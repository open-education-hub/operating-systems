// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>

#include "os_graph.h"
#include "log/log.h"
#include "utils.h"

static int sum;
static os_graph_t *graph;

static void process_node(unsigned int idx)
{
	os_node_t *node;

	node = graph->nodes[idx];
	sum += node->info;
	graph->visited[idx] = DONE;

	for (unsigned int i = 0; i < node->num_neighbours; i++)
		if (graph->visited[node->neighbours[i]] == NOT_VISITED)
			process_node(node->neighbours[i]);
}

int main(int argc, char *argv[])
{
	FILE *input_file;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s input_file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	input_file = fopen(argv[1], "r");
	DIE(input_file == NULL, "fopen");

	graph = create_graph_from_file(input_file);

	process_node(0);

	printf("%d", sum);

	return 0;
}
