// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define EXISTENT_FILE "./existent_file"

/* File exists, open call should succeed. */
int main(void)
{
	int fd;
	int r;

	fd = open(EXISTENT_FILE, 0, 0);
	if (fd == -1)
		exit(EXIT_FAILURE);

	r = close(fd);
	if (r == -1)
		exit(EXIT_FAILURE);

	return 0;
}
