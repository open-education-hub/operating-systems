/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils/utils.h"
#include "utils/sock/sock_util.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

#define LISTEN_BACKLOG	10

unsigned short port = 4242;

int main(void)
{
	int rc;
	int listenfd, sockfd;
	struct sockaddr_in raddr;
	socklen_t raddrlen;
	char buffer[BUFSIZ];

	/* Create socket. */
	listenfd = tcp_create_listener(port, LISTEN_BACKLOG);
	DIE(listenfd < 0, "tpc_create_listener");

	/* Accept connection. */
	sockfd = accept(listenfd, (SSA *) &raddr, &raddrlen);
	DIE(sockfd < 0, "accept");

	/* Read flag from socket. */
	rc = recv(sockfd, buffer, BUFSIZ, 0);
	DIE(rc < 0, "recv");

	printf("Message is: %s\n", buffer);

	close(sockfd);

	return 0;
}
