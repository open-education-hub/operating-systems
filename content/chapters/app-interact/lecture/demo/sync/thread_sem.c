/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#include "utils/utils.h"

#define __unused __attribute__((unused))

static const char * const messages[] = {
	"I",
	" hate",
	" bullshit\n"
};

static sem_t sem_wait_first, sem_wait_second;

static void *first(__unused void *arg)
{
	printf("%s", messages[0]);
	sem_post(&sem_wait_first);

	sem_wait(&sem_wait_second);
	printf("%s", messages[2]);

	return NULL;
}

static void *second(__unused void *arg)
{
	sem_wait(&sem_wait_first);
	printf("%s", messages[1]);
	sem_post(&sem_wait_second);

	return NULL;
}

int main(void)
{
	pthread_t first_tid, second_tid;
	int rc;

	rc = sem_init(&sem_wait_first, 0, 0);
	DIE(rc < 0, "sem_init");

	rc = sem_init(&sem_wait_second, 0, 0);
	DIE(rc < 0, "sem_init");

	rc = pthread_create(&first_tid, NULL, first, NULL);
	DIE(rc < 0, "pthread_create");
	rc = pthread_create(&second_tid, NULL, second, NULL);
	DIE(rc < 0, "pthread_create");

	pthread_join(first_tid, NULL);
	pthread_join(second_tid, NULL);

	sem_destroy(&sem_wait_first);
	sem_destroy(&sem_wait_second);

	return 0;
}
