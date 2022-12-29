// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

#define PORT 		1234

int main(void)
{
	int rc;
	int listenfd, connectfd;
	struct sockaddr_in addr, cli_addr;
	socklen_t cli_addrlen;
	char buffer[BUFSIZ];

	/* Create socket. */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(listenfd < 0, "socket");

	/* Bind socket to address. */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	rc = bind(listenfd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* Put in listen mode. */
	rc = listen(listenfd, 10);
	DIE(rc < 0, "listen");

	/* Make the server run indefinitely. */
	while(1) {
		/* Accept connection. */
		connectfd = accept(listenfd, (struct sockaddr *) &cli_addr, &cli_addrlen);
		DIE(connectfd < 0, "accept");

		/* Receive from client. */
		rc = read(connectfd, buffer, BUFSIZ);
		DIE(rc < 0, "read");

		printf("Received: %s\n", buffer);

		/* Answer with the same string. */
		rc = write(connectfd, buffer, strlen(buffer));
		DIE(rc < 0, "write");
	}

	close(connectfd);
	close(listenfd);

	return 0;
}
