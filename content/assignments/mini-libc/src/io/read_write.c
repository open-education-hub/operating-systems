// SPDX-License-Identifier: BSD-3-Clause

#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>

ssize_t write(int fd, const void *buf, size_t len)
{
	return syscall(__NR_write, fd, buf, len);
}

ssize_t read(int fd, void *buf, size_t len)
{
	return syscall(__NR_read, fd, buf, len);
}
