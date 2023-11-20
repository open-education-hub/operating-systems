// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>

#include "os_graph.h"
#include "log/log.h"
#include "utils.h"

/* Node functions */
os_node_t *os_create_node(unsigned int id, int info)
{
	os_node_t *node;

	node = malloc(sizeof(*node));
	DIE(node == NULL, "mallloc");

	node->id = id;
	node->info = info;
	node->num_neighbours = 0;
	node->neighbours = NULL;

	return node;
}

/* Graph functions */
os_graph_t *create_graph_from_data(unsigned int num_nodes, unsigned int num_edges,
		int *values, os_edge_t *edges)
{
	os_graph_t *graph;

	graph = malloc(sizeof(*graph));
	DIE(graph == NULL, "mallloc");

	graph->num_nodes = num_nodes;
	graph->num_edges = num_edges;

	graph->nodes = malloc(num_nodes * sizeof(os_node_t *));
	DIE(graph->nodes == NULL, "malloc");

	for (unsigned int i = 0; i < graph->num_nodes; i++) {
		graph->nodes[i] = os_create_node(i, values[i]);
		graph->nodes[i]->neighbours = malloc(graph->num_nodes * sizeof(unsigned int));
		DIE(graph->nodes[i]->neighbours == NULL, "malloc");
		graph->nodes[i]->num_neighbours = 0;
	}

	for (unsigned int i = 0; i < graph->num_edges; i++) {
		unsigned int isrc, idst;

		isrc = edges[i].src;
		idst = edges[i].dst;
		graph->nodes[isrc]->neighbours[graph->nodes[isrc]->num_neighbours++] = idst;
		graph->nodes[idst]->neighbours[graph->nodes[idst]->num_neighbours++] = isrc;
	}

	graph->visited = malloc(graph->num_nodes * sizeof(*graph->visited));
	DIE(graph->visited == NULL, "malloc");

	for (unsigned int i = 0; i < graph->num_nodes; i++)
		graph->visited[i] = NOT_VISITED;

	return graph;
}

os_graph_t *create_graph_from_file(FILE *file)
{
	unsigned int num_nodes, num_edges;
	unsigned int i;
	int *nodes;
	os_edge_t *edges;
	os_graph_t *graph = NULL;

	if (fscanf(file, "%d %d", &num_nodes, &num_edges) == 0) {
		log_error("Can't read from file");
		goto out;
	}

	nodes = malloc(num_nodes * sizeof(int));
	DIE(nodes == NULL, "malloc");
	for (i = 0; i < num_nodes; i++) {
		if (fscanf(file, "%d", &nodes[i]) == 0) {
			log_error("Can't read from file");
			goto free_nodes;
		}
	}

	edges = malloc(num_edges * sizeof(os_edge_t));
	DIE(edges == NULL, "malloc");
	for (i = 0; i < num_edges; ++i) {
		if (fscanf(file, "%d %d", &edges[i].src, &edges[i].dst) == 0) {
			log_error("Can't read from file");
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
	for (unsigned int i = 0; i < graph->num_nodes; i++) {
		printf("[%d]: ", i);
		for (unsigned int j = 0; j < graph->nodes[i]->num_neighbours; j++)
			printf("%d ", graph->nodes[i]->neighbours[j]);
		printf("\n");
	}
}
