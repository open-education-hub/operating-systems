/* SPDX-License-Identifier: BSD-3-Clause */

#include <fcntl.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "utils/utils.h"

#define NUM_THREADS			2

#define REDIRECT_STDOUT_FILE_NAME	"redirect_stdout_file.txt"
#define REDIRECT_STDERR_FILE_NAME	"redirect_stderr_file.txt"

struct redirected_print_args {
	int fd;
	void (*redirect_func)();
	const char *message;
};

static pthread_barrier_t barrier;

static void do_stdout_redirect()
{
	int rc;
	int fd;

	fd = open(REDIRECT_STDOUT_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC,
		0644);
	DIE(fd < 0, "open");

	/* Make sure both threads have opened their files. */
	pthread_barrier_wait(&barrier);

	/* TODO: Use `dup2()` instead of `close()` and `dup()`. */
	rc = close(STDOUT_FILENO);
	DIE(rc < 0, "close");

	sleep(3);

	rc = dup(fd);
	DIE(rc < 0, "dup");

	rc = close(fd);
	DIE(rc < 0, "close");
}

static void do_stderr_redirect()
{
	int rc;
	int fd;

	fd = open(REDIRECT_STDERR_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC,
		0644);
	DIE(fd < 0, "open");

	/* Make sure both threads have opened their files. */
	pthread_barrier_wait(&barrier);

	sleep(1);

	/* TODO: Use `dup2()` instead of `close()` and `dup()`. */
	rc = close(STDERR_FILENO);
	DIE(rc < 0, "close");

	rc = dup(fd);
	DIE(rc < 0, "dup");

	rc = close(fd);
	DIE(rc < 0, "close");
}

void *redirected_print(void *arg)
{
	struct redirected_print_args *args = arg;

	args->redirect_func();

	/* Make sure all redirects are made. */
	pthread_barrier_wait(&barrier);

	write(args->fd, args->message, strlen(args->message));

	return NULL;
}

int main(void)
{
	int rc;
	size_t i;
	pthread_t tids[NUM_THREADS];
	struct redirected_print_args args[NUM_THREADS] = {
		{
			.fd = STDOUT_FILENO,
			.redirect_func = do_stdout_redirect,
			.message = "Message for STDOUT\n"
		},
		{
			.fd = STDERR_FILENO,
			.redirect_func = do_stderr_redirect,
			.message = "Message for STDERR\n"
		}
	};

	pthread_barrier_init(&barrier, NULL, NUM_THREADS);

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(&tids[i], NULL, redirected_print, &args[i]);
		DIE(rc < 0, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(tids[i], NULL);
		DIE(rc < 0, "pthread_join");
	}

	pthread_barrier_destroy(&barrier);

	return 0;
}
