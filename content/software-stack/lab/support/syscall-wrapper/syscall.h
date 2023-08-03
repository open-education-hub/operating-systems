/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef SYSCALL_H_
#define SYSCALL_H_	1

int write(int fd, const void *buf, unsigned long count);
void exit(int status);

#endif
