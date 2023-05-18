// SPDX-License-Identifier: BSD-3-Clause

/*
 * Simple reply once server
 *
 * It receives a message and then send an HTTP reply. It is assumed the
 * request is an HTTP request message, but no actual parsing or
 * interpretation is performed.
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

#include "../utils/util.h"
#include "../utils/debug.h"
#include "../utils/sock_util.h"


#define SIMPLE_WEB_LISTEN_PORT		28282


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

	dlog(LOG_INFO, "Accepted connection from %s:%d\n",
		inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	return sockfd;
}

/*
 * Receive (HTTP) request. Don't parse it, just read data in buffer
 * and print it.
 */

static void receive_request(int sockfd)
{
	ssize_t bytes_recv;
	char buffer[BUFSIZ];
	char abuffer[64];
	int rc;

	rc = get_peer_address(sockfd, abuffer, 64);
	if (rc < 0) {
		ERR("get_peer_address");
		goto remove_connection;
	}

	bytes_recv = recv(sockfd, buffer, BUFSIZ, 0);
	if (bytes_recv < 0) {		/* error in communication */
		dlog(LOG_ERR, "Error in communication from %s\n", abuffer);
		goto remove_connection;
	}
	if (bytes_recv == 0) {		/* connection closed */
		dlog(LOG_INFO, "Connection closed from %s\n", abuffer);
		goto remove_connection;
	}

	dlog(LOG_INFO, "Received message from %s\n", abuffer);

	printf("--\n%s--\n", buffer);

	return;

remove_connection:
	/* close local socket */
	close(sockfd);
}

/*
 * Send HTTP reply. Send simple message, don't care about request content.
 *
 * Socket is closed after HTTP reply.
 */

static void send_reply(int sockfd)
{
	ssize_t bytes_sent;
	char abuffer[64];
	int rc;
	char buffer[BUFSIZ] = "HTTP/1.1 200 OK\r\n"
		"Date: Sun, 08 May 2011 09:26:16 GMT\r\n"
		"Server: Apache/2.2.9\r\n"
		"Last-Modified: Mon, 02 Aug 2010 17:55:28 GMT\r\n"
		"Accept-Ranges: bytes\r\n"
		"Content-Length: 153\r\n"
		"Vary: Accept-Encoding\r\n"
		"Connection: close\r\n"
		"Content-Type: text/html\r\n"
		"\r\n"
		"<html><head><meta name=\"google-site-verification\""
		"content=\"gTsIxyV43HSJraRPl6X1A5jzGFgQ3N__hKAcuL2QsO8\" /></head>"
		"<body><h1>It works!</h1></body></html>\r\n";

	rc = get_peer_address(sockfd, abuffer, 64);
	if (rc < 0) {
		ERR("get_peer_address");
		goto remove_connection;
	}

	bytes_sent = send(sockfd, buffer, strlen(buffer), 0);
	if (bytes_sent < 0) {		/* error in communication */
		dlog(LOG_ERR, "Error in communication to %s\n", abuffer);
		goto remove_connection;
	}
	if (bytes_sent == 0) {		/* connection closed */
		dlog(LOG_INFO, "Connection closed to %s\n", abuffer);
		goto remove_connection;
	}

	dlog(LOG_INFO, "Sent message to %s (bytes: %ld)\n", abuffer,
		bytes_sent);

	printf("--\n%s\n--\n", buffer);

	/* Close HTTP connection. */
	close(sockfd);
	return;

remove_connection:
	/* close local socket */
	close(sockfd);
}

int main(void)
{
	int listenfd;	/* server socket */
	int connectfd;		/* client communication socket */

	/* create server socket */
	listenfd = tcp_create_listener(SIMPLE_WEB_LISTEN_PORT,
		DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

	connectfd = accept_connection(listenfd);
	receive_request(connectfd);
	send_reply(connectfd);

	return 0;
}
