/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#include "utils/utils.h"

#define NUM_STEPS	1000000
#define NUM_THREADS	2

static sem_t sem;

static void acquire_lock(void)
{
	int rc = sem_wait(&sem);

	DIE(rc, "sem_wait");
}

static void release_lock(void)
{
	int rc = sem_post(&sem);

	DIE(rc, "sem_post");
}

static unsigned long var = 0;

static void *increase_var(void *arg)
{
	size_t i;

	(void)arg;

	for (i = 0; i < NUM_STEPS; i++) {
		acquire_lock();	/* Begin critical section. */
		var++;
		release_lock();	/* End critical section. */
	}

	return  NULL;
}

int main(void)
{
	int rc;
	size_t i;
	pthread_t tids[NUM_THREADS];

	rc = sem_init(&sem, 0, 1);
	DIE(rc, "sem_init");

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(tids + i, NULL, increase_var, NULL);
		DIE(rc < 0, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(tids[i], NULL);
		DIE(rc < 0, "pthread_create");
	}

	rc = sem_destroy(&sem);
	DIE(rc, "sem_destroy");

	printf("var: %lu\n", var);

	return 0;
}
