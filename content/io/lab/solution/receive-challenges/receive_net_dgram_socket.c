// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

unsigned short port = 4242;

int main(void)
{
	int rc;
	int fd;
	struct sockaddr_in addr;
	socklen_t addrlen;
	char buffer[BUFSIZ];

	/* Create socket. */
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	DIE(fd < 0, "socket");

	/* Bind socket to address. */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	rc = bind(fd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* Read flag from socket. */
	rc = recvfrom(fd, buffer, BUFSIZ, 0, (struct sockaddr *) &addr, &addrlen);
	DIE(rc < 0, "recvfrom");

	printf("Flag is: %s\n", buffer);

	close(fd);

	return 0;
}
