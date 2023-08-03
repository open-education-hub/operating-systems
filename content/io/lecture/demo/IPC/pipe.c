// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "utils/utils.h"

#define PIPE_READ_FD    0
#define PIPE_WRITE_FD   1

static const char *heisenberg = "I am the one who knocks!";

int main(void)
{
	pid_t pid;
	int rc;
	char buf[32];
	int pipe_fd[2];

	// Create pipe
	rc = pipe(pipe_fd);
	DIE(rc < 0, "pipe");

	pid = fork();
	switch (pid) {
		case -1:	/* Error */
			DIE(1, "fork");
			break;

		case 0:
			// Close unused write end
			close(pipe_fd[PIPE_WRITE_FD]);

			rc = read(pipe_fd[PIPE_READ_FD], buf, 32);
			DIE(rc < 0, "read");

			buf[rc] = '\0';
			printf("%s\n", buf);

			close(pipe_fd[PIPE_READ_FD]);
			return 42;

		default:	/* Parent process */
			// Close unused read end
			close(pipe_fd[PIPE_READ_FD]);

			rc = write(pipe_fd[PIPE_WRITE_FD], heisenberg, strlen(heisenberg));
			DIE(rc < 0, "write");

			close(pipe_fd[PIPE_WRITE_FD]);
			break;
	}

	return 0;
}
