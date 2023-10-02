// SPDX-License-Identifier: BSD-3-Clause

#include "os_list.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

os_queue_t *queue_create(void)
{
	os_queue_t *queue;

	queue = malloc(sizeof(*queue));
	if (queue == NULL) {
		perror("malloc");
		return NULL;
	}
	pthread_mutex_init(&queue->lock, NULL);
	queue->first =  NULL;
	queue->last = NULL;

	return queue;
}

void queue_add(os_queue_t *queue, void *info)
{
	os_list_node_t *node;

	node = malloc(sizeof(*node));
	if (node == NULL) {
		fprintf(stderr, "[ERROR] %s: Not enough memory\n", __func__);
		return;
	}

	node->next = NULL;
	node->info = info;

	if (queue->last == NULL && queue->first == NULL) {
		queue->first = node;
		queue->last = node;
	} else {
		queue->last->next = node;
		queue->last = node;
	}
}

os_list_node_t *queue_get(os_queue_t *queue)
{
	os_list_node_t *target;

	if (queue == NULL)
		return NULL;
	if (queue->first == NULL && queue->last == NULL)
		return NULL;

	target = queue->first;
	queue->first = queue->first->next;

	return target;
}
