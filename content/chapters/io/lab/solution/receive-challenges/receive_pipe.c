// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

static pid_t create_process_with_redirect(const char *path, int new_stdin,
	int new_stdout, int new_stderr)
{
	pid_t pid;
	int rc;

	pid = fork();
	switch (pid) {
	case -1:	/* Error */
		DIE(pid < 0, "fork");
		break;

	case 0:		/* Child process */
		if (new_stdin != -1)
			dup2(new_stdin, 0);
		if (new_stdout != -1)
			dup2(new_stdout, 1);
		if (new_stderr != -1)
			dup2(new_stderr, 2);

		rc = execl(path, path, NULL);
		DIE(rc < 0, "execl");
	}

	return pid;
}

int main(void)
{
	int pipefd[2];
	char buf[BUFSIZ];
	int rc;

	rc = pipe(pipefd);
	DIE(rc < 0, "pipe");

	log_info("Created pipe with descriptors %d and %d.\n", pipefd[0],
		pipefd[1]);

	/* Create child process. Ignore the PID return value. */
	create_process_with_redirect(
		"../../support/receive-challenges/send_fd_4", -1, pipefd[1],
		-1);

	/**
	 * Child process writes to `pipefd[1]`, parent process reads from
	 * `pipefd[0]`.
	 */
	close(pipefd[1]);

	rc = read(pipefd[0], buf, BUFSIZ);
	DIE(rc < 0, "read");

	printf("Flag is: %s\n", buf);

	/* Wait for child process. */
	wait(NULL);

	return 0;
}
