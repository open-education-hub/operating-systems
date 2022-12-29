// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
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

static const char server_socket_path[] = "tower_bridge";
static const char client_socket_path[] = "bifrost";
static const char message[] = "R2-D2 is underrated";

int main(void)
{
	int rc;
	int fd;
	struct sockaddr_un saddr, caddr;
	char buffer[BUFSIZ];

	/* UNIX server socket must exist. It must be created by receiver. */
	rc = access(server_socket_path, R_OK | W_OK);
	DIE(rc < 0, "access");

	/* Create client socket. */
	fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	DIE(fd < 0, "open");

	/* Fill client info. */
	memset(&caddr, 0, sizeof(caddr));
	caddr.sun_family = AF_UNIX;
	snprintf(caddr.sun_path, sizeof(client_socket_path)+1, "%s", client_socket_path);

	/* Bind client socket to client info. */
	rc = bind(fd, (struct sockaddr *) &caddr, sizeof(caddr));
	DIE(rc < 0, "bind");

	/* Fill server info. */
	memset(&saddr, 0, sizeof(saddr));
	saddr.sun_family = AF_UNIX;
	snprintf(saddr.sun_path, sizeof(server_socket_path)+1, "%s", server_socket_path);

	/* Send to server. */
	rc = sendto(fd, message, sizeof(message), 0, (struct sockaddr *) &saddr, sizeof(saddr));
	DIE(rc < 0, "sendto");

	/* Wait reply. */
	rc = recvfrom(fd, buffer, BUFSIZ, 0, NULL, NULL);
	DIE(rc < 0, "recvfrom");

	printf("Received: %s\n", buffer);

	close(fd);
	remove(caddr.sun_path);
	return 0;
}
