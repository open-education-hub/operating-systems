// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include "os_graph.h"
#include "os_threadpool.h"
#include "os_list.h"

#define MAX_TASK 100
#define MAX_THREAD 4

static int sum;
static os_graph_t *graph;
/* REMOVE 80 */
static pthread_mutex_t sum_lock, visited_lock;

typedef struct {
	os_threadpool_t *tp;
	os_graph_t *graph;
	unsigned int current_node;
} os_arg_t;

static void process_neighbours(void *args)
{
	os_arg_t *my_args = (os_arg_t *)args;
	os_threadpool_t *threadpool = my_args->tp;
	os_graph_t *graph = my_args->graph;
	unsigned int current = my_args->current_node;
	os_arg_t *new_args;

	pthread_mutex_lock(&sum_lock);
	sum += graph->nodes[current]->info;
	pthread_mutex_unlock(&sum_lock);

	for (int i = 0; i < graph->nodes[current]->num_neighbours; ++i) {
		unsigned int neighbour;

		neighbour = graph->nodes[current]->neighbours[i];
		pthread_mutex_lock(&visited_lock);
		if (graph->visited[neighbour] == 0) {
			os_task_t *new_task;

			graph->visited[neighbour] = 1;
			pthread_mutex_unlock(&visited_lock);
			new_args = calloc(1, sizeof(*new_args));
			new_args->tp = threadpool;
			new_args->graph = graph;
			new_args->current_node = (unsigned int) graph->nodes[current]->neighbours[i];
			new_task = task_create((void *) new_args, process_neighbours);
			add_task_in_queue(threadpool, new_task);
		} else {
			pthread_mutex_unlock(&visited_lock);
		}
	}
}

static void traverse_graph_parallel(os_threadpool_t *tp)
{
	int i;

	for (i = 0; i < graph->num_nodes; ++i) {
		pthread_mutex_lock(&visited_lock);
		if (graph->visited[i] == 0) {
			os_arg_t *new_arg;
			os_task_t *new_task;

			graph->visited[i] = 1;
			pthread_mutex_unlock(&visited_lock);
			new_arg = calloc(1, sizeof(*new_arg));
			new_arg->tp = tp;
			new_arg->graph = graph;
			new_arg->current_node = (unsigned int) i;
			new_task = task_create((void *) new_arg, process_neighbours);
			add_task_in_queue(tp, new_task);
		} else {
			pthread_mutex_unlock(&visited_lock);
		}
	}
}

static int processing_is_done(os_threadpool_t *tp)
{
	/* If any of the nodes are not visited, we're not done. */
	for (unsigned int i = 0; i < graph->num_nodes; i++)
		if (graph->visited[i] == 0)
			return 0;

	/* If there still are tasks we are not done. */
	if (tp->tasks)
		return 0;

	/* All nodes are visited and no tasks in task queue */
	return 1;
}

int main(int argc, char *argv[])
{
	FILE *input_file;
	/* REMOVE 1 */
	os_threadpool_t *threadpool;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s input_file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	input_file = fopen(argv[1], "r");
	if (input_file == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	graph = create_graph_from_file(input_file);
	if (graph == NULL) {
		fprintf(stderr, "[Error] Can't read the graph from file\n");
		exit(EXIT_FAILURE);
	}

	/* TODO: Create thread pool and traverse the graph. */

	printf("%d", sum);

	return 0;
}
