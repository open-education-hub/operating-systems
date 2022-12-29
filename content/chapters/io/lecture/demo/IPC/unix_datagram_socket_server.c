// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

static const char socket_path[] = "tower_bridge";

int main(void)
{
	int rc;
	int fd;
	struct sockaddr_un addr, raddr;
	socklen_t raddrlen = sizeof(raddr);
	char buffer[BUFSIZ];

	/* Remove socket_path. */
	remove(socket_path);

	/* Create socket. */
	fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	DIE(fd < 0, "socket");

	/* Bind socket to path. */
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, strlen(socket_path)+1, "%s", socket_path);
	rc = bind(fd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* Make server run indefinitely. */
	while (1) {
		/* Receive from client. */
		rc = recvfrom(fd, buffer, BUFSIZ, 0, (struct sockaddr *) &raddr, &raddrlen);
		DIE(rc < 0, "recvfrom");

		printf("Received: %s\n", buffer);
		/* Answer with the same string. */
		raddrlen = sizeof(raddr);
		rc = sendto(fd, buffer, strlen(buffer), 0, (struct sockaddr *) &raddr, raddrlen);
		DIE(rc < 0, "sendto");
	}

	close(fd);

	return 0;
}
