/* SPDX-License-Identifier: BSD-3-Clause */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "utils/utils.h"

static const char fifo_path[] = "../../support/receive-challenges/apollodorus";

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

int main(void)
{
	int rc;
	int fd;
	char buffer[BUFSIZ];

	/**
	 * Create FIFO if it doesn't exist or if it exists and has incorrect
	 * permissions.
	 */
	rc = access(fifo_path, R_OK | W_OK);
	if (rc < 0) {
		remove(fifo_path);
		rc = mkfifo(fifo_path, 0755);
		DIE(rc < 0, "mkfifo");
	}

	/* Open FIFO. */
	fd = open(fifo_path, O_RDONLY);
	DIE(fd < 0, "open");

	/* Read flag from FIFO. */
	rc = read(fd, buffer, BUFSIZ);
	DIE(rc < 0, "read");

	printf("Flag is: %s\n", buffer);

	return 0;
}
