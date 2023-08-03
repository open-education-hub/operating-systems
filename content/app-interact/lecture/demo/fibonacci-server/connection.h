/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef CONNECTION_H_
#define CONNECTION_H_	1

int accept_connection(int listenfd);
void handle_connection(int connectfd);

#endif /* CONNECTION_H_ */
