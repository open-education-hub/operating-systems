/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils/utils.h"

int main(void)
{
	pid_t ret_pid;
	pid_t pid;
	int status;

	pid = fork();
	switch (pid) {
	case -1:
		/* `fork()` has encountered an error. */
		DIE(1, "fork");
		break;

	case 0:
		/* Child process */
		printf("[child 1] current PID = %d; parent PID = %d\n",
			getpid(), getppid());

		/**
		 * TODO 2: Create another child process here and print its PID
		 * and PPID.
		 */

		/**
		 * TODO 1: Return a different value from the child and see
		 * `status` change in the parent.
		 */
		break;

	default:
		/* Parent process */
		printf("[parent] child PID = %d; current PID = %d\n", pid,
			getpid());

		ret_pid = waitpid(pid, &status, 0);
		DIE(ret_pid < 0, "waitpid parent");

		if (WIFEXITED(status))
			printf("[parent] Child process exited with status %d\n",
				WEXITSTATUS(status));
		break;
	}

	return 0;
}
