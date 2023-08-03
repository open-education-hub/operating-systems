/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

#include "../utils/utils.h"

#define BIND_ADDR "0.0.0.0"
#define PORT 2000

int create_socket(char *addr, short port)
{
	int sockfd;
	struct sockaddr_in srv_addr;
	int ret;
	int val;

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	DIE(sockfd < 0, "socket");

	val = 1;

	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	DIE(ret < 0, "setsockopt");

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	ret = inet_aton(addr, &srv_addr.sin_addr);
	DIE(!ret, "Invalid IP address");

	ret = bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	DIE(ret < 0, "bind");

	ret = listen(sockfd, 10);
	DIE(ret < 0, "listen");

	return sockfd;
}

int xsend(int sockfd, const void *buf, size_t len, int flags)
{
	int ret;
	size_t i = 0;
	const char *p = (const char *)buf;

	while (i < len) {
		ret = send(sockfd, &p[i], len-i, flags);
		if (ret < 0)
			return ret;

		if (ret == 0)
			break;

		i += ret;
	}

	return i;
}

int handle_client(int sockfd)
{
	int ret;
	time_t current_time;
	uint32_t size;

	current_time = htobe64(time(NULL));

	size = htonl(sizeof(current_time));

	ret = xsend(sockfd, &size, sizeof(size), 0);
	DIE(ret < 0, "send");

	ret = xsend(sockfd, &current_time, sizeof(current_time), 0);
	DIE(ret < 0, "send");

	return 1;
}

int main()
{
	int sockfd;

	sockfd = create_socket(BIND_ADDR, PORT);
	DIE(sockfd < 0, "Failed to create socket\n");

	while (1) {
		struct sockaddr_in cl_addr;
		int cl_sockfd;
		socklen_t addr_len = sizeof(cl_addr);

		cl_sockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &addr_len);
		DIE(cl_sockfd < 0, "accept");

		printf("Got connection from %s:%d\n", inet_ntoa(cl_addr.sin_addr), ntohs(cl_addr.sin_port));

		handle_client(cl_sockfd);

		close(cl_sockfd);
	}

	return 0;
}
