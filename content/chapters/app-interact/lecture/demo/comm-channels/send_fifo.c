/* SPDX-License-Identifier: BSD-3-Clause */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "utils/utils.h"

static const char fifo_path[] = "fifo_channel";
static const char message[] = "Hello, world!";

int main(void)
{
	int rc;
	int fd;

	/* FIFO must exist. It must be created by receiver. */
	rc = access(fifo_path, R_OK | W_OK);
	DIE(rc < 0, "access");

	/* Open FIFO. */
	fd = open(fifo_path, O_RDWR);
	DIE(fd < 0, "open");

	/* Write message to FIFO. */
	rc = write(fd, message, sizeof(message));
	DIE(rc < 0, "write");

	return 0;
}
