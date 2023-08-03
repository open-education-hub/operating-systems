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
	struct sockaddr_in addr, raddr;
	socklen_t raddrlen;
	char buffer[BUFSIZ];

	/* Create socket. */
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	DIE(fd < 0, "socket");

	/* TODO: Bind socket to address. */


	/* TODO: Read flag from socket. */


	printf("Flag is: %s\n", buffer);

	close(fd);

	return 0;
}
