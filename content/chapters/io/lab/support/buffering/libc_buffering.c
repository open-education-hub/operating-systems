/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "utils/utils.h"

#define USEC_PER_SEC	1000000
#define MSEC_PER_SEC	1000

#define READ		0
#define WRITE		1

static unsigned long diff_msec(struct timeval start, struct timeval end)
{
	return (USEC_PER_SEC * (end.tv_sec - start.tv_sec) + end.tv_usec -
		start.tv_usec) / MSEC_PER_SEC;
}

int main(int argc, char *argv[])
{
	char c = 'x';
	int rc;
	int mode;
	char *mode_str;
	long total_bytes = 0;
	struct stat statbuf;
	FILE *f;
	struct timeval start, end;

	DIE(argc != 3, "Usage: ./no_buffering read/write <file>");

	if (!strcmp(argv[1], "read")) {
		mode_str = "r";
		mode = READ;
	} else if (!strcmp(argv[1], "write")) {
		mode_str = "w";
		mode = WRITE;
	} else {
		DIE(1, "Invalid mode");
	}

	rc = stat(argv[2], &statbuf);
	DIE(rc == -1, "stat");

	f = fopen(argv[2], mode_str);
	DIE(!f, "fopen");

	gettimeofday(&start, NULL);

	/* Read or write from / to the file 1 byte at a time. */
	while (total_bytes < statbuf.st_size) {
		if (mode == READ) {
			rc = fread(&c, 1, 1, f);
			DIE(rc == -1, "fread");
		} else {
			rc = fwrite(&c, 1, 1, f);
			DIE(rc == -1, "fwrite");
		}

		total_bytes++;
	}

	gettimeofday(&end, NULL);

	if (mode == READ)
		printf("Read %zu bytes from %s in %lu ms\n", total_bytes,
			argv[2], diff_msec(start, end));
	else
		printf("Wrote %zu bytes to %s in %lu ms\n", total_bytes,
			argv[2], diff_msec(start, end));

	rc = fclose(f);
	DIE(rc == -1, "close");

	return 0;
}
