/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __UNISTD_H__
#define __UNISTD_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/io.h>
#include <internal/types.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_DATA 3
#define SEEK_HOLE 4

int close(int fd);
off_t lseek(int fd, off_t offset, int whence);
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
unsigned int sleep(unsigned int seconds);

#ifdef __cplusplus
}
#endif

#endif
