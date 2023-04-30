// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "sock-utils.h"

const char *localhost = "127.0.0.1";

int main(void)
{
	char buf[BUFSIZE];
	int ret, sockfd;
	struct sockaddr_in receiver_addr;
	struct sockaddr_in sender_addr;
	socklen_t sender_addr_len;

	/* Create a socket. */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(sockfd < 0, "socket");

	/* TODO 1: Add address and port to receiver_addr. */
	/* HINT: use populate_sockaddr(). */

	/* TODO 2: Bind sockfd to receiver_addr. Use DIE to check for errors. */

	printf("Server with PID %d is listening for data on port %d ...\n", getpid(), PORT);

	while (1) {
		/* TODO 2.1: Remove break. */
		break;

		/* Prepare the buffer */
		memset(buf, 0, BUFSIZE);

		/* TODO 3: Receive at most BUFSIZE bytes through the socket with recvfrom(). */
		/* HINT: Use sender_addr as the fifth arg. You will need to cast it. */
		/*       It will be populated with information about the sender. */
		/* Use DIE to check for errors. */

		/* Ensure buf is null-terminated. */
		buf[BUFSIZE-1] = '\0';

		/* Print the message. */
		printf("Received from IP %s and port %d: %s\n", inet_ntoa(sender_addr.sin_addr),
			sender_addr.sin_port, buf);

		if (strncmp(buf, "exit", 4) == 0)
			break;
	}

	/* Close the socket. */
	ret = close(sockfd);
	DIE(ret < 0, "close");

	return 0;
}
