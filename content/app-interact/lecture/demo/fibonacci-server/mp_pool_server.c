/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/prctl.h>
#include <signal.h>

#include "utils/utils.h"
#include "utils/log/log.h"
#include "utils/sock/sock_util.h"

#include "./task.h"
#include "./connection.h"

static struct task_set *ts;

static void handle(void)
{
	/* Get task and serve non-stop. */
	while (1) {
		struct task *t;

		t = get_task(ts);
		handle_connection(t->fd);
	}
}

static void create_process_pool(size_t num_processes)
{
	pid_t pid, parent_pid;
	size_t i;
	int rc;

	parent_pid = getpid();
	for (i = 0; i < num_processes; i++) {
		pid = fork();
		switch (pid) {
		case -1:
			DIE(pid < 0, "fork");
			break;
		case 0:
			/* Terminate process when parent exits. */
			rc = prctl(PR_SET_PDEATHSIG, SIGTERM);
			DIE(rc < 0, "prctl");
			/*
			 * Test in case the original parent exited just
			 * before the prctl() call.
			 */
			if (getppid() != parent_pid)
				 exit(EXIT_FAILURE);
			handle();
			break;
		default:
			break;
		}
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
	ts = create_task_set(MAX_CAPACITY, 1);
	DIE(ts == NULL, "create_task_set");

	num_cores = get_nprocs();
	log_info("Creating pool of %ld processes\n", num_cores);
	create_process_pool(num_cores);

	log_info("Starting server on port %d", port);
	run_server(port);

	return 0;
}
