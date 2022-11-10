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

#include "./connection.h"

int listenfd;

static void handle(void)
{
	int connectfd;	/* client communication socket */

	/* Get task and serve non-stop. */
	while (1) {
		connectfd = accept_connection(listenfd);
		DIE(connectfd < 0, "accept_connection");

		handle_connection(connectfd);
	}
}

static void create_process_pool(size_t num_processes, int port)
{
	pid_t pid, parent_pid;
	size_t i;
	int rc;

	/* create server socket */
	listenfd = tcp_create_listener(port, DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

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

	/* Parent process itself does the handling. */
	handle();
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

	num_cores = get_nprocs() - 1;
	log_info("Creating pool of %ld processes\n", num_cores);
	create_process_pool(num_cores, port);

	return 0;
}
