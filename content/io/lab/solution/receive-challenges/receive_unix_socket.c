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

static const char socket_path[] = "../../support/receive-challenges/golden_gate";

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
	listenfd = socket(PF_UNIX, SOCK_STREAM, 0);
	DIE(listenfd < 0, "socket");

	/* Bind socket to path. */
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, socket_path);
	rc = bind(listenfd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* Put in listen mode. */
	rc = listen(listenfd, 10);
	DIE(rc < 0, "listen");

	/* Accept connection. */
	connectfd = accept(listenfd, (struct sockaddr *) &raddr, &raddrlen);
	DIE(connectfd < 0, "accept");

	/* Read flag from socket. */
	rc = read(connectfd, buffer, BUFSIZ);
	DIE(rc < 0, "read");

	printf("Flag is: %s\n", buffer);

	close(connectfd);
	close(listenfd);

	return 0;
}
