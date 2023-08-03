/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils/utils.h"

unsigned short remote_port = 4242;
static const char message[] = "Hello, world!";

int main(void)
{
	int rc;
	int fd;
	struct sockaddr_in raddr;

	/* Create socket. */
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	DIE(fd < 0, "socket");

	/* Define remote address. */
	memset(&raddr, 0, sizeof(raddr));
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(remote_port);
	raddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	/* Write flag to socket. */
	rc = sendto(fd, message, sizeof(message), 0, (struct sockaddr *) &raddr, sizeof(raddr));
	DIE(rc < 0, "sendto");

	close(fd);

	return 0;
}
