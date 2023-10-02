// SPDX-License-Identifier: BSD-3-Clause

#include "os_graph.h"
#include <stdio.h>
#include <stdlib.h>

/* Node functions */
os_node_t *os_create_node(unsigned int id, int info)
{
	os_node_t *node;

	node = calloc(1, sizeof(*node));

	node->id = id;
	node->info = info;

	return node;
}

/* Graph functions */
os_graph_t *create_graph_from_data(unsigned int num_nodes, unsigned int num_edges,
		int *values, os_edge_t *edges)
{
	int i, isrc, idst;
	os_graph_t *graph;

	graph = calloc(1, sizeof(*graph));

	graph->num_nodes = num_nodes;
	graph->num_edges = num_edges;

	graph->nodes = calloc(num_nodes, sizeof(os_node_t *));

	for (i = 0; i < num_nodes; ++i) {
		graph->nodes[i] = os_create_node(i, values[i]);
		graph->nodes[i]->neighbours = calloc(num_nodes, sizeof(unsigned int));
		graph->nodes[i]->num_neighbours = 0;
	}

	for (i = 0; i < num_edges; ++i) {
		isrc = edges[i].src; idst = edges[i].dst;
		graph->nodes[isrc]->neighbours[graph->nodes[isrc]->num_neighbours++] = idst;
		graph->nodes[idst]->neighbours[graph->nodes[idst]->num_neighbours++] = isrc;
	}

	graph->visited = calloc(graph->num_nodes, sizeof(*graph->visited));

	return graph;
}

os_graph_t *create_graph_from_file(FILE *file)
{
	unsigned int num_nodes, num_edges;
	int i;
	int *nodes;
	os_edge_t *edges;
	os_graph_t *graph = NULL;

	if (fscanf(file, "%d %d", &num_nodes, &num_edges) == 0) {
		fprintf(stderr, "[ERROR] Can't read from file\n");
		goto out;
	}

	nodes = malloc(num_nodes * sizeof(int));
	for (i = 0; i < num_nodes; ++i) {
		if (fscanf(file, "%d", &nodes[i]) == 0) {
			fprintf(stderr, "[ERROR] Can't read from file\n");
			goto free_nodes;
		}
	}

	edges = malloc(num_edges * sizeof(os_edge_t));
	for (i = 0; i < num_edges; ++i) {
		if (fscanf(file, "%d %d", &edges[i].src, &edges[i].dst) == 0) {
			fprintf(stderr, "[ERROR] Can't read from file\n");
			goto free_edges;
		}
	}

	graph = create_graph_from_data(num_nodes, num_edges, nodes, edges);

free_edges:
	free(edges);
free_nodes:
	free(nodes);
out:
	return graph;
}

void print_graph(os_graph_t *graph)
{
	int i, j;

	for (i = 0; i < graph->num_nodes; ++i) {
		printf("[%d]: ", i);
		for (j = 0; j < graph->nodes[i]->num_neighbours; ++j)
			printf("%d ", graph->nodes[i]->neighbours[j]);
		printf("\n");
	}
}
