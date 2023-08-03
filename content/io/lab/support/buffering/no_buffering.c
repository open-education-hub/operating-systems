/* SPDX-License-Identifier: BSD-3-Clause */

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils/utils.h"

#define USEC_PER_SEC 1000000
#define MSEC_PER_SEC 1000

static unsigned long diff_msec(struct timeval start, struct timeval end)
{
	return (USEC_PER_SEC * (end.tv_sec - start.tv_sec) + end.tv_usec -
		start.tv_usec) / MSEC_PER_SEC;
}

int main(int argc, char *argv[])
{
	char c = 'x';
	int fd;
	int rc;
	int mode;
	long total_bytes = 0;
	struct stat statbuf;
	struct timeval start, end;

	DIE(argc != 3, "Usage: ./no_buffering read/write <file>");

	if (!strcmp(argv[1], "read"))
		mode = O_RDONLY;
	else if (!strcmp(argv[1], "write"))
		mode = O_WRONLY;
	else
		DIE(1, "Invalid mode");

	fd = open(argv[2], mode);
	DIE(fd == -1, "open");

	rc = fstat(fd, &statbuf);
	DIE(rc == -1, "fstat");

	gettimeofday(&start, NULL);

	/* Read or write from / to the file 1 byte at a time. */
	while (total_bytes < statbuf.st_size) {
		if (mode == O_RDONLY) {
			rc = read(fd, &c, 1);
			DIE(rc == -1, "read");
		} else {
			rc = write(fd, &c, 1);
			DIE(rc == -1, "write");
		}

		total_bytes++;
	}

	gettimeofday(&end, NULL);

	if (mode == O_RDONLY)
		printf("Read %zu bytes from %s in %lu ms\n", total_bytes,
			argv[2], diff_msec(start, end));
	else
		printf("Wrote %zu bytes to %s in %lu ms\n", total_bytes,
			argv[2], diff_msec(start, end));

	rc = close(fd);
	DIE(rc == -1, "close");

	return 0;
}
