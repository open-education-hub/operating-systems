/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils/utils.h"
#include "utils/sock/sock_util.h"

unsigned short remote_port = 4242;
static const char message[] = "Hello, world!";

int main(void)
{
	int rc;
	int fd;
	int sockfd;

	/* Create socket. */
	fd = socket(PF_INET, SOCK_STREAM, 0);
	DIE(fd < 0, "socket");

	sockfd = tcp_connect_to_server("localhost", remote_port);
	DIE(sockfd < 0, "tcp_connect_to_server");

	/* Write message to socket. */
	rc = send(sockfd, message, sizeof(message), 0);
	DIE(rc < 0, "send");

	close(sockfd);

	return 0;
}
