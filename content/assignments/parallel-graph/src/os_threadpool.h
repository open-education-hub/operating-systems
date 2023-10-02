/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __SO_THREADPOOL_H__
#define __SO_THREADPOOL_H__	1

#include <pthread.h>

typedef struct {
	void *argument;
	void (*task)(void *args);
} os_task_t;

typedef struct _node {
	os_task_t *task;
	struct _node *next;
} os_task_queue_t;

typedef struct {
	unsigned int should_stop;

	unsigned int num_threads;
	pthread_t *threads;

	os_task_queue_t *tasks;
	pthread_mutex_t lock;
} os_threadpool_t;

os_task_t *task_create(void *arg, void (*f)(void *));
void add_task_in_queue(os_threadpool_t *tp, os_task_t *t);
os_task_t *get_task(os_threadpool_t *tp);
os_threadpool_t *threadpool_create(unsigned int num_tasks, unsigned int num_threads);
void *thread_loop_function(void *args);
void threadpool_stop(os_threadpool_t *tp, int (*processing_is_complete)(os_threadpool_t *));

#endif
