// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#include "utils/utils.h"
#include "utils/get_time.h"

#define NUM_STEPS	1000000
#define NUM_THREADS	2

static pthread_spinlock_t lock;

static void acquire_lock(void)
{
	int rc = pthread_spin_lock(&lock);

	DIE(rc, "pthread_spin_lock");
}

static void release_lock(void)
{
	int rc = pthread_spin_unlock(&lock);

	DIE(rc, "pthread_spin_unlock");
}

static int var;

static void *increase_var(void *arg)
{
	size_t i;

	(void)arg;

	for (i = 0; i < NUM_STEPS; ++i) {
		acquire_lock();	/* Begin critical section. */
		++var;
		release_lock();	/* End critical section. */
	}

	return  NULL;
}

int main(void)
{
	int rc;
	void *retval;
	size_t i;
	pthread_t tids[NUM_THREADS];
	u_int64_t millis_start;
	u_int64_t millis_end;

	rc = pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
	DIE(rc, "pthread_spin_init");

	millis_start = get_current_millis();

	for (i = 0; i < NUM_THREADS; ++i) {
		rc = pthread_create(tids + i, NULL, increase_var, NULL);
		DIE(rc < 0, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(tids[i], &retval);
		DIE(rc < 0, "pthread_create");
	}

	millis_end = get_current_millis();

	rc = pthread_spin_destroy(&lock);
	DIE(rc, "pthread_spin_destroy");

	printf("var = %d; time = %lu ms\n", var, millis_end - millis_start);

	return 0;
}
