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

#define IP_ADDR 	"127.0.0.1"
#define PORT 		1234

static const char message[] = "R2-D2 is underrated";

int main(void)
{
	int rc;
	int fd;
	struct sockaddr_in addr;
	char buffer[BUFSIZ];

	/* Create socket. */
	fd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(fd < 0, "open");

	/* Connect socket to server. */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	rc = inet_aton(IP_ADDR, &addr.sin_addr);
	DIE(rc == 0, "inet_aton");

	rc = connect(fd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "connect");

	/* Send to server. */
	rc = write(fd, message, sizeof(message));
	DIE(rc < 0, "write");

	/* Wait reply. */
	rc = read(fd, buffer, sizeof(buffer));
	DIE(rc < 0, "read");

	printf("Received: %s\n", buffer);

	close(fd);

	return 0;
}
