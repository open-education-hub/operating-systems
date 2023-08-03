// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define FILENAME	"./file"

int main(void)
{
	/* Try to open a file that doesn't exit. Open should return -1, and errno should be set to -ENOENT. */
	int fd;
	int r;

	fd = open(FILENAME, 0, 0);
	if (fd == -1 && errno == ENOENT) {
		write(1, "Open returned error - trying to open file that doesn't exist.\n",
			strlen("Open returned error - trying to open file that doesn't exist.\n"));
	} else {
		close(fd);
		write(1, "Something went wrong - open.\n", strlen("Something went wrong - open.\n"));
	}

	/* Try to open a file that doesn't exit, specify the O_CREAT flag. Open should succeed. */
	fd = open(FILENAME, O_CREAT, S_IRUSR);
	if (fd >= 0)
		write(1, "Open success - trying to open file that doesn't exist, O_CREAT was specified.\n",
			strlen("Open success - trying to open file that doesn't exist, O_CREAT was specified.\n"));
	else
		write(1, "Something went wrong - open.\n", strlen("Something went wrong - open.\n"));

	/* Try to close the file descriptor. */
	r = close(fd);
	if (r < 0)
		write(1, "Something went wrong - close.\n", strlen("Something went wrong - close.\n"));

	return 0;
}
