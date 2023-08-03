/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "utils/utils.h"

#define __unused __attribute__((unused))

static const char * const messages[] = {
	"I",
	" hate",
	" bullshit\n"
};

enum state {
	MESSAGE_NOT_PRINTED = 0,
	MESSAGE_PRINTED = 1
};

static enum state message_states[] = {
	MESSAGE_NOT_PRINTED,
	MESSAGE_NOT_PRINTED,
	MESSAGE_NOT_PRINTED
};

static pthread_cond_t cond_wait_first, cond_wait_second;
static pthread_mutex_t cond_mutex;

static void *first(__unused void *arg)
{
	pthread_mutex_lock(&cond_mutex);

	printf("%s", messages[0]);
	message_states[0] = MESSAGE_PRINTED;
	pthread_cond_signal(&cond_wait_first);

	while (message_states[1] != MESSAGE_PRINTED)
		pthread_cond_wait(&cond_wait_second, &cond_mutex);

	printf("%s", messages[2]);
	message_states[0] = MESSAGE_PRINTED;

	pthread_mutex_unlock(&cond_mutex);

	return NULL;
}

static void *second(__unused void *arg)
{
	pthread_mutex_lock(&cond_mutex);

	while (message_states[0] != MESSAGE_PRINTED)
		pthread_cond_wait(&cond_wait_first, &cond_mutex);

	printf("%s", messages[1]);
	message_states[1] = MESSAGE_PRINTED;
	pthread_cond_signal(&cond_wait_second);

	pthread_mutex_unlock(&cond_mutex);

	return NULL;
}

int main(void)
{
	pthread_t first_tid, second_tid;
	int rc;

	rc = pthread_cond_init(&cond_wait_first, NULL);
	DIE(rc < 0, "pthread_cond_init");

	rc = pthread_cond_init(&cond_wait_second, NULL);
	DIE(rc < 0, "pthread_cond_init");

	rc = pthread_mutex_init(&cond_mutex, NULL);
	DIE(rc < 0, "pthread_mutex");

	rc = pthread_create(&first_tid, NULL, first, NULL);
	DIE(rc < 0, "pthread_create");
	rc = pthread_create(&second_tid, NULL, second, NULL);
	DIE(rc < 0, "pthread_create");

	pthread_join(first_tid, NULL);
	pthread_join(second_tid, NULL);

	pthread_cond_destroy(&cond_wait_first);
	pthread_cond_destroy(&cond_wait_second);
	pthread_mutex_destroy(&cond_mutex);

	return 0;
}
