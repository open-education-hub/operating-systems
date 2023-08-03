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

static const char socket_path[] = "golden_gate";

int main(void)
{
	int rc;
	int listenfd, connectfd;
	struct sockaddr_un addr, raddr;
	socklen_t raddrlen;
	char buffer[BUFSIZ];

	/* Remove socket_path. */
	remove(socket_path);

	/* Create socket. */
	listenfd = socket(AF_UNIX, SOCK_STREAM, 0);
	DIE(listenfd < 0, "socket");

	/* Bind socket to path. */
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, strlen(socket_path)+1, "%s", socket_path);
	rc = bind(listenfd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* Put in listen mode. */
	rc = listen(listenfd, 10);
	DIE(rc < 0, "listen");

	/* Make server run indefinitely. */
	while(1) {
		/* Accept connection. */
		connectfd = accept(listenfd, (struct sockaddr *) &raddr, &raddrlen);
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
