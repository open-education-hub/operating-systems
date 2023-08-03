// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define EXISTENT_FILE	"./existent_file"
#define FILE_SIZE	20

/* Open file with size 20, perform lseek operations, check returned offsets */
int main(void)
{
	int fd;
	off_t offset;
	int r;

	fd = open(EXISTENT_FILE, 0, 0);
	if (fd < 0)
		exit(EXIT_FAILURE);

	offset = lseek(fd, 10, SEEK_SET);
	if (offset != 10)
		exit(EXIT_FAILURE);

	offset = lseek(fd, 10, SEEK_CUR);
	if (offset != 20)
		exit(EXIT_FAILURE);

	offset = lseek(fd, 10, SEEK_END);
	if (offset != 30)
		exit(EXIT_FAILURE);

	r = close(fd);
	if (r < 0)
		exit(EXIT_FAILURE);

	return 0;
}
