// SPDX-License-Identifier: BSD-3-Clause

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Import user configuration: */
#include <uk/config.h>

#include <uk/sched.h>
#include <uk/schedcoop.h>

#define NUM_THREADS	2
#define NUM_STEPS	4

static void thread_func(void *arg)
{
	int i;
	int tid = *(int *)arg;

	printf("Thread %d created!\n", tid);

	for (i = 0; i < NUM_STEPS; i++) {
		printf("Thread %d: step %d\n", tid, i);

#ifdef CONFIG_APPSCHEDULETHREADS_COOPERATE
		uk_sched_yield();
#endif
	}

	printf("Thread %d finished!\n", tid);

#ifndef CONFIG_APPSCHEDULETHREADS_COOPERATE
		uk_sched_yield();
#endif
}

int main(int argc, char *argv[])
{
	size_t jobs[NUM_THREADS];
	pthread_t threads[NUM_THREADS];

	for (size_t i = 0; i < NUM_THREADS; ++i) {
		jobs[i] = i + 1;
		pthread_create(threads+i, NULL, thread_func, jobs+i);
	}

	for (size_t i = 0; i < NUM_THREADS; ++i)
		pthread_join(threads[i], NULL);

	return EXIT_SUCCESS;
}
