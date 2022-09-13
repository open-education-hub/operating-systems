/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#include "utils/utils.h"

#define __unused __attribute__((unused))

static void wait_for_input(const char *msg)
{
	char buffer[128];

	printf("%s ...", msg);
	fgets(buffer, 128, stdin);
}

static void *sleep_wrapper(void __unused *data)
{
	sleep(100);
	return NULL;
}

#define NUM_THREADS	5

int main(void)
{
	size_t i;
	pthread_t tid[NUM_THREADS];
	int rc;

	wait_for_input("Press key to start creating threads");

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(&tid[i], NULL, sleep_wrapper, NULL);
		DIE(rc < 0, "pthread_create");
		wait_for_input("Press key to create new thread");
	}

	wait_for_input("Press key to wait for threads");
	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
