/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "utils/utils.h"
#include "utils/log/log.h"
#include "utils/sock/sock_util.h"

#include "./connection.h"

static void *thread_handle(void *arg)
{
	int connectfd = (int) ((long) arg);

	handle_connection(connectfd);

	return NULL;
}

static void handle_in_new_thread(int connectfd)
{
	int rc;
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	rc = pthread_create(&tid, &attr, thread_handle, (void *) (long) connectfd);
	if (rc != 0) {
		ERR(rc != 0, "pthread_create");
		close(connectfd);
		goto end;
	}

	log_info("Created thread with ID %lu to handle connection.", tid);

end:
	pthread_attr_destroy(&attr);
}

static void run_server(int port)
{
	int listenfd;		/* server socket */
	int connectfd;		/* client communication socket */

	/* create server socket */
	listenfd = tcp_create_listener(port, DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

	while (1) {
		connectfd = accept_connection(listenfd);
		DIE(connectfd < 0, "accept_connection");
		handle_in_new_thread(connectfd);
	}
}

int main(int argc, char **argv)
{
	int port;

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

	log_info("Starting server on port %d", port);
	run_server(port);

	return 0;
}
