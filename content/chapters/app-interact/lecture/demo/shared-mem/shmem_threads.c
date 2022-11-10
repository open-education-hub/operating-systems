/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#include "utils/utils.h"

#define __unused __attribute__((unused))

static sem_t writer_write_1;
static sem_t writer_write_2;
static sem_t reader_read_1;

static int shared_value = 0;

#define VALUE_1		100
#define VALUE_2		200

static void *writer(__unused void *arg)
{
	shared_value = VALUE_1;
	sem_post(&writer_write_1);

	sem_wait(&reader_read_1);
	shared_value = VALUE_2;
	sem_post(&writer_write_2);

	return NULL;
}

static void *reader(__unused void *arg)
{
	sem_wait(&writer_write_1);
	printf("read %d\n", shared_value);
	sem_post(&reader_read_1);

	sem_wait(&writer_write_2);
	printf("read %d\n", shared_value);

	return NULL;
}

int main(void)
{
	pthread_t writer_tid;
	pthread_t reader_tid;
	int rc;

	rc = sem_init(&writer_write_1, 0, 0);
	DIE(rc < 0, "sem_init");
	rc = sem_init(&writer_write_2, 0, 0);
	DIE(rc < 0, "sem_init");
	rc = sem_init(&reader_read_1, 0, 0);
	DIE(rc < 0, "sem_init");

	rc = pthread_create(&writer_tid, NULL, writer, NULL);
	DIE(rc < 0, "pthread_create");
	rc = pthread_create(&reader_tid, NULL, reader, NULL);
	DIE(rc < 0, "pthread_create");

	pthread_join(writer_tid, NULL);
	pthread_join(reader_tid, NULL);

	return 0;
}
