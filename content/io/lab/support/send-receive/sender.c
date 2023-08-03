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

int read_input_with_prompt(char *buf)
{
	char *ret;

	printf("Message for receiver (type 'exit' to quit): ");

	memset(buf, 0, BUFSIZE);
	ret = fgets(buf, BUFSIZE, stdin);
	if (!ret)
		return -1;
	buf[strlen(buf)-1] = '\0';

	return 0;
}

int main(void)
{
	char buf[BUFSIZE];
	int ret, sockfd;
	struct sockaddr_in receiver_addr;

	/* Create a socket. */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(sockfd < 0, "socket");

	/* TODO 1: Add address and port to receiver_addr. */
	/* HINT: use populate_sockaddr(). */

	while (1) {
		ret = read_input_with_prompt(buf);
		DIE(ret < 0, "read_input_with_prompt");

		/* TODO 2: Send message from buf through the socket with sendto(). */
		/* HINT: Use receiver_addr as the fifth arg. You will need to cast it. */
		/* Use DIE to check for errors. */

		if (strncmp(buf, "exit", 4) == 0)
			break;
	}

	/* Close the socket */
	ret = close(sockfd);
	DIE(ret < 0, "close");

	return 0;
}
