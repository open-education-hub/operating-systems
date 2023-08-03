// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define READ_ONLY_FILE	"./read_only_file"

/*
 * Call open on read-only file with access mode = write.
 * Open should fail and errno should be set to -EACCES.
 */

int main(void)
{
	int fd;

	fd = open(READ_ONLY_FILE, O_WRONLY, 0);
	if (fd != -1 || errno != -EACCES)
		exit(EXIT_FAILURE);

	return 0;
}
