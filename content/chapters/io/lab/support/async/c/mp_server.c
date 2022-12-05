/*
 * SPDX-License-Identifier: BSD-3-Clause
 */

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

#include "utils/utils.h"
#include "utils/log/log.h"
#include "utils/sock/sock_util.h"


/*
 * Compute Fibonacci number.
 */

static unsigned long fibonacci(unsigned long num)
{
	if (num == 0 || num == 1)
		return 1;
	return fibonacci(num-1) + fibonacci(num-2);
}

/*
 * Handle a new connection request on the server socket.
 */

static int accept_connection(int listenfd)
{
	int sockfd;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in addr;

	/* accept new connection */
	sockfd = accept(listenfd, (SSA *) &addr, &addrlen);
	DIE(sockfd < 0, "accept");

	log_info("Accepted connection from %s:%d",
		inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	return sockfd;
}

/*
 * Receive data from socket. Handle possible errors.
 *
 * Return number of bytes received, -1 at error.
 */

static int receive_data(int sockfd, char *buffer, size_t len)
{
	ssize_t bytes_recv;
	char abuffer[64];
	int rc;

	rc = get_peer_address(sockfd, abuffer, 64);
	if (rc < 0) {
		log_error("get_peer_address");
		goto error;
	}

	bytes_recv = recv(sockfd, buffer, len, 0);
	if (bytes_recv < 0) {		/* error in communication */
		log_error("Error in communication from %s", abuffer);
		goto error;
	}
	if (bytes_recv == 0) {		/* connection closed */
		log_info("Connection closed from %s", abuffer);
		goto error;
	}
	buffer[bytes_recv] = '\0';

	log_debug("Received message from %s", abuffer);
	log_debug("--%s--", buffer);

	return bytes_recv;

error:
	return -1;
}

/*
 * Send data to socket. Handle possible errors.
 *
 * Return number of bytes sent, -1 at error.
 */

static int send_data(int sockfd, char *buffer, size_t len)
{
	ssize_t bytes_sent;
	char abuffer[64];
	int rc;

	rc = get_peer_address(sockfd, abuffer, 64);
	if (rc < 0) {
		log_error("get_peer_address");
		goto error;
	}

	bytes_sent = send(sockfd, buffer, len, 0);
	if (bytes_sent < 0) {		/* error in communication */
		log_error("Error in communication to %s", abuffer);
		goto error;
	}
	if (bytes_sent == 0) {		/* connection closed */
		log_info("Connection closed to %s", abuffer);
		goto error;
	}

	log_debug("Sent message to %s", abuffer);
	log_debug("--%s--", buffer);

	return bytes_sent;

error:
	return -1;
}

static void handle(int connectfd)
{
	char buffer[BUFSIZ];
	ssize_t bytes;
	unsigned long num;

	/* Read data. */
	bytes = receive_data(connectfd, buffer, BUFSIZ);
	if (bytes < 0)
		goto end;

	num = (unsigned int) strtoul(buffer, NULL, 10);
	if (errno == ERANGE) {
		snprintf("%s", sizeof(buffer), buffer, "out of range");
		goto send;
	}

	if (num > 34) {
		snprintf("%s", sizeof(buffer), buffer, "out of range");
		goto send;
	}

	num = fibonacci(num);
	snprintf(buffer, BUFSIZ, "%lu", num);

send:
	/* Send data. Fall through, irrespective of result. */
	send_data(connectfd, buffer, strlen(buffer));

end:
	close(connectfd);
}

static void handle_in_new_process(int connectfd)
{
	pid_t pid;

	pid = fork();
	switch (pid) {
	case -1:
		ERR(pid != 0, "fork");
		break;
	case 0:		/* child process */
		daemon(1, 1);
		handle(connectfd);
		exit(EXIT_SUCCESS);
		break;
	default:
		log_info("Created process with ID %d to handle connection.", pid);
		break;
	}

	close(connectfd);
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
		handle_in_new_process(connectfd);
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
