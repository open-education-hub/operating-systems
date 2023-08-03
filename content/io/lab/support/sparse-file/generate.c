/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#include "utils/utils.h"

#define FILENAME "swiss_cheese.sparse"
#define NUM_SPACES 10

static const char FLAG[] = "SO{all_for_the_empire}";

int main(void)
{
	int fd;
	size_t i;

	fd = open(FILENAME, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	DIE(fd < 0, "open");

	for (i = 0; i < sizeof(FLAG); i++) {
		ssize_t n;
		off_t pos;

		n = write(fd, FLAG+i, 1);
		DIE(n < 0, "write");

		pos = lseek(fd, NUM_SPACES, SEEK_CUR);
		DIE(pos < 0, "lseek");
	}

	close(fd);

	return 0;
}
