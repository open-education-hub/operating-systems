/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __OS_LIST_H__
#define __OS_LIST_H__	1

#include <pthread.h>

typedef struct os_list_node_t {
	void *info;
	struct os_list_node_t *next;
} os_list_node_t;

typedef struct  {
	struct os_list_node_t *first;
	struct os_list_node_t *last;
	pthread_mutex_t lock;
} os_queue_t;

os_queue_t *queue_create(void);
void queue_add(os_queue_t *queue, void *info);
os_list_node_t *queue_get(os_queue_t *queue);

#endif
