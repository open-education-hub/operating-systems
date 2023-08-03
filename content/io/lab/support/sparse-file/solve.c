/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include "utils/utils.h"

#define FILENAME "../../support/sparse-file/swiss_cheese.sparse"
#define NUM_SPACES 10

#ifndef BUFSIZ
#define BUFSIZ	256
#endif

int main(void)
{
	int fd;
	size_t i;
	char buffer[BUFSIZ];

	fd = open(FILENAME, O_RDONLY);
	DIE(fd < 0, "open");

	for (i = 0; i < BUFSIZ; i++) {
		ssize_t n;
		off_t pos;

		/* TODO: Read character. */


		/* TODO: Stop if no more characters (read returns 0). */


		/* TODO: Skep NUM_SPACES blank characters. */
	}

	printf("flag is %s\n", buffer);

	close(fd);

	return 0;
}
