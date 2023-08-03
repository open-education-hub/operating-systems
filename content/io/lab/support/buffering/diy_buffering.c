/* SPDX-License-Identifier: BSD-3-Clause */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils/utils.h"

#define USEC_PER_SEC	1000000
#define MSEC_PER_SEC	1000

#define BUFSIZE		4096

#define MIN(a, b)	((a) < (b) ? (a) : (b))

static char buf[BUFSIZE];
/* Starting and end offsets in `buf`. */
static ssize_t buf_start, buf_end;

static unsigned long diff_msec(struct timeval start, struct timeval end)
{
	return (USEC_PER_SEC * (end.tv_sec - start.tv_sec) + end.tv_usec -
		start.tv_usec) / MSEC_PER_SEC;
}

static size_t diy_fread(void *dst, size_t size, size_t nmemb, int fd)
{
	ssize_t to_read = size * nmemb;
	size_t dst_pos = 0;
	size_t to_copy;

	while (to_read) {
		if (buf_start == buf_end) {
			/* Buffer is empty. Fill it. */
			buf_end = read(fd, buf, BUFSIZE);
			DIE(buf_end == -1, "read");

			buf_start = 0;
		}

		/* Copy data from the buffer to `dst`. */
		to_copy = MIN(to_read, buf_end - buf_start);
		memcpy(dst + dst_pos, buf + buf_start, to_copy);

		/* Update all offsets. */
		buf_start += to_copy;
		dst_pos += to_copy;
		to_read -= to_copy;
	}

	return nmemb;
}

static size_t diy_fwrite(void *src, size_t size, size_t nmemb, int fd)
{
	ssize_t to_write = size * nmemb;
	size_t src_pos = 0;
	size_t to_copy;

	while (to_write) {
		/**
		 * TODO: write the data first to `buf` and to the file when it
		 * fills up.
		 */
	}

	return nmemb;
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

	DIE(argc != 3, "Usage: ./diy_buffering read/write <file>");

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
		if (mode == O_RDONLY)
			diy_fread(&c, 1, 1, fd);
		else
			diy_fwrite(&c, 1, 1, fd);

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
