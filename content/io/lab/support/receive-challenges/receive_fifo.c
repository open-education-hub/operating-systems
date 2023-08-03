/* SPDX-License-Identifier: BSD-3-Clause */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "utils/utils.h"

static const char fifo_path[] = "apollodorus";

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
		/**
		 * TODO: `access()` has returned an error, so you need to create
		 * the FIFO yourself.
		 */
	}

	/* TODO: Open FIFO for reading. */


	/* TODO: Read flag from FIFO. */


	printf("Flag is: %s\n", buffer);

	return 0;
}
