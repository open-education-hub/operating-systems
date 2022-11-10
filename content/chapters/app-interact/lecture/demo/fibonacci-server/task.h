/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef TASK_H_
#define TASK_H_		1

#include <semaphore.h>

#define MAX_CAPACITY	100

struct task {
	int fd;
};

struct task_set {
	size_t capacity;
	size_t num_items;
	struct task **tasks;
	size_t read_index;
	size_t write_index;
	sem_t *lock;
	sem_t *empty;
	sem_t *filled;
};

struct task *create_task(int fd);
void destroy_task(struct task *t);
struct task_set *create_task_set(size_t capacity, int pshared);
void destroy_task_set(struct task_set *ts);
void put_task(struct task_set *ts, struct task *t);
struct task *get_task(struct task_set *ts);

#endif
