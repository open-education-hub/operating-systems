// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdatomic.h>

#include "utils/utils.h"
#include "utils/get_time.h"

#define NUM_STEPS	1000000
#define NUM_THREADS	2

static int var;

static void *increase_var(void *arg)
{
	size_t i;

	(void)arg;

	for (i = 0; i < NUM_STEPS; ++i)
		atomic_fetch_add(&var, 1);

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

	printf("var = %d; time = %lu ms\n", var, millis_end - millis_start);

	return 0;
}
