/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef SYSCALL_H_
#define SYSCALL_H_	1

int read(int fd, void *buf, unsigned long count);
int write(int fd, const void *buf, unsigned long count);
int getpid(void);
void exit(int status);

#endif
