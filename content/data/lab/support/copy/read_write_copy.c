/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "utils/utils.h"

#define SRC_FILENAME	"in.dat"
#define DST_FILENAME	"out.dat"

#define diff_us(ta, tb)		\
	(((ta).tv_sec - (tb).tv_sec) * 1000 * 1000 + \
	 ((ta).tv_nsec - (tb).tv_nsec) / 1000)

#define BUFSIZE		8192

static unsigned char buffer[BUFSIZE];

int main(void)
{
	int src_fd, dst_fd;
	ssize_t n;
	struct timespec time_before, time_after;

	src_fd = open(SRC_FILENAME, O_RDONLY);
	DIE(src_fd < 0, "open");

	dst_fd = open(DST_FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
	DIE(dst_fd < 0, "open");

	clock_gettime(CLOCK_REALTIME, &time_before);
	while (1) {
		n = read(src_fd, buffer, BUFSIZE);
		DIE(n < 0, "read");

		if (n == 0)
			break;

		/* Assume everything is written. */
		n = write(dst_fd, buffer, n);
		DIE(n < 0, "write");
	}
	clock_gettime(CLOCK_REALTIME, &time_after);
	printf("time passed %ld microseconds\n", diff_us(time_after, time_before));

	close(src_fd);
	close(dst_fd);

	return 0;
}
