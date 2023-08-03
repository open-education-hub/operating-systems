/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <pthread.h>

#include "utils/utils.h"
#include "utils/log/log.h"
#include "utils/sock/sock_util.h"

#include "./task.h"
#include "./connection.h"

#define __unused __attribute__((unused))

static struct task_set *ts;

static void *handle(__unused void *arg)
{
	/* Get task and serve non-stop. */
	while (1) {
		struct task *t;

		t = get_task(ts);
		handle_connection(t->fd);
	}

	return NULL;
}

static void create_thread_pool(size_t num_threads)
{
	pthread_t tid;
	pthread_attr_t attr;
	size_t i;
	int rc;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	for (i = 0; i < num_threads; i++) {
		rc = pthread_create(&tid, &attr, handle, NULL);
		DIE(rc < 0, "pthread_create");
	}
}

static void run_server(int port)
{
	int listenfd;		/* server socket */

	/* create server socket */
	listenfd = tcp_create_listener(port, DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

	while (1) {
		struct task *t;
		int connectfd;	/* client communication socket */

		connectfd = accept_connection(listenfd);
		DIE(connectfd < 0, "accept_connection");

		/* Create task and it to task list. */
		t = create_task(connectfd);
		DIE(t == NULL, "create_task");

		put_task(ts, t);
	}
}

int main(int argc, char **argv)
{
	int port;
	long num_cores;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = (int) strtol(argv[1], NULL, 10);
	DIE(errno == ERANGE, "strtol");

	if (port < 0 || port > 65535) {
		fprintf(stderr, "Invalid port %d\n", port);
		exit(EXIT_FAILURE);
	}

	/* Create task set. */
	ts = create_task_set(MAX_CAPACITY, 0);
	DIE(ts == NULL, "create_task_set");

	num_cores = get_nprocs();
	log_info("Creating pool of %ld threads\n", num_cores);
	create_thread_pool(num_cores);

	log_info("Starting server on port %d", port);
	run_server(port);

	return 0;
}
