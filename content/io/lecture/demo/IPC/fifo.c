// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "utils/utils.h"

#define FIFO_NAME "my_fifo"

static const char *heisenberg = "I am the one who knocks!";

int main(void)
{
	pid_t pid;
	int fifo_fd;
	char buf[32];
	int rc;

	/* Remove old FIFO. */
	remove(FIFO_NAME);

	/* Create FIFO. */
	rc = mkfifo(FIFO_NAME, 0644);
	DIE(rc < 0, "mkfifo");

	pid = fork();
	switch (pid)
	{
		case -1: /* Error */
			DIE(1, "fork");
			break;

		case 0: /* Child process */
			fifo_fd = open(FIFO_NAME, O_RDONLY);
			DIE(fifo_fd < 0, "open");

			/* Read from pipe and print. */
			rc = read(fifo_fd, buf, 32);
			DIE(rc < 0, "read");
			buf[rc] = '\0';
			printf("%s\n", buf);

			close(fifo_fd);
			return 42;

		default: /* Parent process */
			fifo_fd = open(FIFO_NAME, O_WRONLY);
			DIE(fifo_fd < 0, "open");

			/* Write to pipe. */
			rc = write(fifo_fd, heisenberg, strlen(heisenberg));
			DIE(rc < 0, "write");

			close(fifo_fd);
			break;
	}

	return 0;
}
