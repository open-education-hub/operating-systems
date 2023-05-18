// SPDX-License-Identifier: BSD-3-Clause

#define _GNU_SOURCE
#include <dlfcn.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sendfile.h>

ssize_t (*orig_send)(int sockfd, const void *buf, size_t len, int flags);
ssize_t (*orig_recv)(int sockfd, void *buf, size_t len, int flags);
ssize_t (*orig_sendfile)(int out_fd, int in_fd, off_t *offset, size_t count);

ssize_t send(int sockfd, const void *buf, size_t len, int flags)
{
	if (len > 1)
		len /= 2;

	return orig_send(sockfd, buf, len, flags);
}

ssize_t recv(int sockfd, void *buf, size_t len, int flags)
{
	if (len > 20)
		len = 20;
	else if (len > 1)
		len /= 2;

	return orig_recv(sockfd, buf, len, flags);
}

ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count)
{
	if (count > 32)
		count /= 2;

	return orig_sendfile(out_fd, in_fd, offset, count);
}

void _init(void)
{
	orig_send = dlsym(RTLD_NEXT, "send");
	orig_recv = dlsym(RTLD_NEXT, "recv");
	orig_sendfile = dlsym(RTLD_NEXT, "sendfile");
}

