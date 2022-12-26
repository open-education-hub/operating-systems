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
	int fd;
	struct sockaddr_in addr, cli_addr;
	socklen_t addrlen = sizeof(cli_addr);
	char buffer[BUFSIZ];

	/* Create socket. */
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(fd < 0, "socket");

	/* Bind socket to address. */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	rc = bind(fd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* Make the server run indefinitely. */
	while(1) {
		/* Receive from client. */
		rc = recvfrom(fd, buffer, BUFSIZ, 0, (struct sockaddr *) &cli_addr, &addrlen);
		DIE(rc < 0, "recvfrom");

		printf("Received: %s\n", buffer);

		/* Answer with the same string. */
		addrlen = sizeof(cli_addr);
		rc = sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr *)&cli_addr, addrlen);
		DIE(rc < 0, "sendto");
	}

	close(fd);

	return 0;
}
