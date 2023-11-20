/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __OS_GRAPH_H__
#define __OS_GRAPH_H__	1

#include <stdio.h>

typedef struct os_node_t {
	unsigned int id;
	int info;

	unsigned int num_neighbours;
	unsigned int *neighbours;
} os_node_t;

typedef struct os_graph_t {
	unsigned int num_nodes;
	unsigned int num_edges;

	os_node_t **nodes;
	enum {
		NOT_VISITED = 0,
		PROCESSING = 1,
		DONE = 2
	} *visited;
} os_graph_t;

typedef struct os_edge_t {
	unsigned int src, dst;
} os_edge_t;

os_node_t *os_create_node(unsigned int id, int info);
os_graph_t *create_graph_from_data(unsigned int num_nodes, unsigned int num_edges,
		int *values, os_edge_t *edges);
os_graph_t *create_graph_from_file(FILE *file);
void print_graph(os_graph_t *graph);

#endif
