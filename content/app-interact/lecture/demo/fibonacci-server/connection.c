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
#include <errno.h>

#include "utils/log/log.h"
#include "utils/sock/sock_util.h"
#include "utils/utils.h"

#include "connection.h"

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

/*
 * Create new connection with client.
 */

int accept_connection(int listenfd)
{
	int sockfd;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in addr;

	/* Accept new connection. */
	sockfd = accept(listenfd, (SSA *) &addr, &addrlen);
	if (sockfd < 0) {
		ERR(sockfd < 0, "accept");
		return -1;
	}

	log_info("Accepted connection from %s:%d",
		inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	return sockfd;
}

/*
 * Handle a new connection.
 */

void handle_connection(int connectfd)
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
		snprintf(buffer, sizeof(buffer), "%s", "out of range");
		goto send;
	}

	if (num > 34) {
		snprintf(buffer, sizeof(buffer), "%s", "out of range");
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
