/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <endian.h>

#include "../utils/utils.h"

#define MAX_SIZE 8

int connect_to_server(char *ip, char *port_str)
{
	int sockfd;
	int ret;
	struct sockaddr_in addr;
	short port;
	char *pend;

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	DIE(sockfd < 0, "socket");

	addr.sin_family = AF_INET;

	ret = inet_aton(ip, &addr.sin_addr);
	DIE(!ret, "Invalid ip");

	port = strtoul(port_str, &pend, 10);
	DIE(!*port_str || *pend, "Invalid port");

	addr.sin_port = htons(port);

	ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	DIE(ret < 0, "connect");

	return sockfd;
}

int xrecv(int sockfd, void *buf, size_t len, int flags)
{
	int ret;
	size_t i = 0;
	char *p = (char *)buf;

	while (i < len) {
		ret = recv(sockfd, &p[i], len-i, flags);
		if (ret < 0)
			return ret;

		if (ret == 0)
			break;

		i += ret;
	}

	return i;
}

int main(int argc, char *argv[])
{
	int sockfd;
	int ret;

	uint32_t size;
	uint64_t val;
	time_t current_time;

	if (argc != 3) {
		fprintf(stderr, "Usage: client ip port\n");
		return 1;
	}

	sockfd = connect_to_server(argv[1], argv[2]);
	DIE(sockfd < 0, "Failed to create socket");

	ret = xrecv(sockfd, &size, sizeof(size), 0);
	DIE(ret < 0, "recv");
	DIE(ret != sizeof(size), "EOF");

	size = be32toh(size);

	DIE(size > MAX_SIZE, "Invalid size");

	ret = xrecv(sockfd, &val, size, 0);
	DIE(ret < 0, "recv");
	DIE(ret != size, "EOF");

	if (size == 4) {
	    current_time = ntohl(val);
	} else if (size == 8) {
	    current_time = be64toh(val);
	}

	printf("The time is %s", ctime(&current_time));

	close(sockfd);

	return 0;
}
