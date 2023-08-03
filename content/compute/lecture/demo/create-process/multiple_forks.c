// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils/utils.h"

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Press ENTER to continue ...\n");
	fflush(stdout);
	fgets(buf, 32, stdin);
}

int main(void)
{
	pid_t pid;
	int rc;
	int exit_code;

	fork();
	printf("After first fork: PID = %d; PPID = %d\n", getpid(), getppid());
	wait_for_input("first fork()");

	fork();
	printf("After second fork: PID = %d; PPID = %d\n", getpid(), getppid());
	wait_for_input("second fork()");

	pid = fork();
	wait_for_input("third fork()");

	switch (pid) {
	case -1:	/* Error */
		DIE(1, "fork");
		break;

	case 0: 	/* Child process */
		sleep(1);
		printf("[child] PID = %d; PPID = %d\n", getpid(), getppid());

		break;

	default: 	/* Parent process */
		printf("[parent] PID = %d; child PID = %d; Waiting...\n",
			getpid(), pid);

		rc = waitpid(pid, &exit_code, 0);
		DIE(rc < 0, "waitpid");

		break;
	}

	return 0;
}
