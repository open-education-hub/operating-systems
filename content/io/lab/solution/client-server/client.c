// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils/utils.h"

#define PORT	5000
#define BUFSIZE	1024

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

void populate_sockaddr(struct sockaddr_in *sockaddr, const char *addr, int port)
{
	int ret;

	sockaddr->sin_family = AF_INET;
	sockaddr->sin_port = htons(port);
	ret = inet_aton(addr, (struct in_addr *) &sockaddr->sin_addr.s_addr);
	DIE(ret == 0, "inet_aton");
}

int main(void)
{
	char buf[BUFSIZE];
	int ret, sockfd;
	struct sockaddr_in server_addr;

	while (1) {
		/* Get user input as a string. */
		ret = read_input_with_prompt(buf);
		DIE(ret < 0, "read_input_with_prompt");

		/* TODO 1: Create a TCP socket (SOCK_STREAM). */
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		DIE(sockfd < 0, "socket");

		/* TODO 2: Add address and port to server_addr. */
		/* HINT: use populate_sockaddr(). */
		populate_sockaddr(&server_addr, localhost, PORT);

		/* TODO 3: Connect to the server. */
		/* Use DIE to check for errors. */
		ret = connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
		DIE(ret < 0, "connect");

		/* TODO 4: Send message from buf through the socket with send(). */
		ret = send(sockfd, buf, strlen(buf), 0);
		DIE(ret < 0, "send");

		/* If the message is "exit", break out of the loop. */
		if (strncmp(buf, "exit", 4) == 0)
			break;

		/* TODO 5: Receive the response from the server with recv(). */
		ret = recv(sockfd, buf, BUFSIZE, 0);
		DIE(ret < 0, "recv");
		buf[ret-1] = '\0';

		/* Print the response. */
		printf("Received from server: %s\n", buf);

		/* TODO 6: Close the socket. */
		ret = close(sockfd);
		DIE(ret < 0, "close");
	}

	return 0;
}
