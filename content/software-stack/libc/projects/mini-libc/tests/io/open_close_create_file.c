// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define CREATE_FILE	"./create_file"

/* File does not exist, O_CREAT is specified, open call should succeed. */
int main(void)
{
	int fd;
	int r;

	fd = open(CREATE_FILE, O_CREAT, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
	if (fd < 0)
		exit(EXIT_FAILURE);

	r = close(fd);
	if (r < 0)
		exit(EXIT_FAILURE);

	return 0;
}
