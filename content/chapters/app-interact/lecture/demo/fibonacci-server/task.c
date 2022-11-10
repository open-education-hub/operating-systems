/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <sys/mman.h>
#include <semaphore.h>

#include "utils/log/log.h"
#include "utils/utils.h"

#include "./task.h"

struct task *create_task(int fd)
{
	struct task *t;

	t = mmap(NULL, sizeof(*t), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (t == MAP_FAILED)
		return NULL;

	t->fd = fd;

	return t;
}

void destroy_task(struct task *t)
{
	munmap(t, sizeof(*t));
}

struct task_set *create_task_set(size_t capacity, int pshared)
{
	struct task_set *ts;
	int rc;

	if (capacity > MAX_CAPACITY)
		goto out_null;

	ts = mmap(NULL, sizeof(*ts), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ts == MAP_FAILED)
		goto out_null;

	ts->capacity = capacity;
	ts->num_items = 0;
	ts->read_index = 0;
	ts->write_index = 0;

	ts->empty = mmap(NULL, sizeof(*(ts->empty)), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ts->empty == MAP_FAILED)
		goto free_ts;

	ts->filled = mmap(NULL, sizeof(*(ts->filled)), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ts->filled == MAP_FAILED)
		goto free_empty;

	ts->lock = mmap(NULL, sizeof(*(ts->lock)), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ts->lock == MAP_FAILED)
		goto free_filled;

	ts->tasks = mmap(NULL, ts->capacity * sizeof(*(ts->tasks)), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ts->tasks == MAP_FAILED)
		goto free_lock;

	rc = sem_init(ts->empty, pshared, ts->capacity);
	if (rc < 0)
		goto free_tasks;
	rc = sem_init(ts->filled, pshared, 0);
	if (rc < 0)
		goto destroy_empty;
	rc = sem_init(ts->lock, pshared, 1);
	if (rc < 0)
		goto destroy_filled;

	return ts;

destroy_filled:
	sem_destroy(ts->filled);
destroy_empty:
	sem_destroy(ts->empty);
free_tasks:
	munmap(ts->tasks, capacity * sizeof(*(ts->tasks)));
free_lock:
	munmap(ts->lock, sizeof(*(ts->lock)));
free_filled:
	munmap(ts->filled, sizeof(*(ts->filled)));
free_empty:
	munmap(ts->empty, sizeof(*(ts->empty)));
free_ts:
	munmap(ts, sizeof(*ts));
out_null:
	return NULL;
}

void destroy_task_set(struct task_set *ts)
{
	sem_destroy(ts->lock);
	sem_destroy(ts->filled);
	sem_destroy(ts->empty);
	munmap(ts->tasks, ts->capacity * sizeof(*(ts->tasks)));
	munmap(ts->lock, sizeof(*(ts->lock)));
	munmap(ts->filled, sizeof(*(ts->filled)));
	munmap(ts->empty, sizeof(*(ts->empty)));
	munmap(ts, sizeof(*ts));
}

void put_task(struct task_set *ts, struct task *t)
{
	sem_wait(ts->empty);

	sem_wait(ts->lock);
	ts->tasks[ts->write_index] = t;
	ts->write_index = (ts->write_index + 1) % ts->capacity;
	ts->num_items++;
	sem_post(ts->lock);

	sem_post(ts->filled);
}

struct task *get_task(struct task_set *ts)
{
	struct task *t;

	sem_wait(ts->filled);

	sem_wait(ts->lock);
	t = ts->tasks[ts->read_index];
	ts->read_index = (ts->read_index + 1) % ts->capacity;
	ts->num_items--;
	sem_post(ts->lock);

	sem_post(ts->empty);

	return t;
}
