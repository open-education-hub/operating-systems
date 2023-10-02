// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include "os_graph.h"

static int sum;
static os_graph_t *graph;

static void process_node(unsigned int idx)
{
	os_node_t *node;

	node = graph->nodes[idx];
	sum += node->info;
	for (int i = 0; i < node->num_neighbours; i++)
		if (graph->visited[node->neighbours[i]] == 0) {
			graph->visited[node->neighbours[i]] = 1;
			process_node(node->neighbours[i]);
		}
}

static void traverse_graph(void)
{
	for (int i = 0; i < graph->num_nodes; i++) {
		if (graph->visited[i] == 0) {
			graph->visited[i] = 1;
			process_node(i);
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *input_file;

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

	traverse_graph();
	printf("%d", sum);

	return 0;
}
