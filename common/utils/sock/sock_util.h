/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Useful socket macros and structures
 */

#ifndef SOCK_UTIL_H_
#define SOCK_UTIL_H_	1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* default backlog for listen(2) system call */
#define DEFAULT_LISTEN_BACKLOG		5

/* "shortcut" for struct sockaddr structure */
#define SSA			struct sockaddr


int tcp_connect_to_server(const char *name, unsigned short port);
int tcp_close_connection(int s);
int tcp_create_listener(unsigned short port, int backlog);
int get_peer_address(int sockfd, char *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif
