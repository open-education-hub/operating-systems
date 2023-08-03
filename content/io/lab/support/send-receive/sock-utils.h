/* SPDX-License-Identifier: BSD-3-Clause */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils/utils.h"

#define PORT	5000
#define BUFSIZE	1024

void populate_sockaddr(struct sockaddr_in *sockaddr, const char *addr, int port)
{
	int ret;

	sockaddr->sin_family = AF_INET;
	sockaddr->sin_port = htons(port);
	ret = inet_aton(addr, (struct in_addr *)&sockaddr->sin_addr.s_addr);
	DIE(ret == 0, "inet_aton");
}
