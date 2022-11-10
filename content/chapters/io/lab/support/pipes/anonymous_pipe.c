// SPDX-License-Identifier: BSD-3-Clause

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils/utils.h"

#define BUFSIZE 	128
#define EXIT_STR	"exit"
#define PIPE_READ	0
#define PIPE_WRITE	1

static bool check_for_exit(const char *input)
{
	if (strcmp(input, EXIT_STR) == 0) {
		return true;
	}

	return false;
}

static void child_loop(int readfd)
{
	char output[BUFSIZE];
	int rc;

	while (1) {
		rc = read(readfd, output, BUFSIZE);
		DIE(rc < 0, "read");

		if (rc == 0) {
			/* TODO: Close pipe head used for reading. */
			break;
		}

		printf("[Child received]: %s\n", output);
		fflush(stdout);
	}

	return;
}

static void parent_loop(int writefd)
{
	char input[BUFSIZE];
	int rc;

	while (1) {
		memset(input, 0, BUFSIZE);
		scanf("%s",  input);

		if (check_for_exit(input)) {
			/* TODO: Close pipe head used for writing. */
			break;
		}

		rc = write(writefd, input, BUFSIZE);
		DIE(rc < 0, "write");
	}

	return;
}

static void wait_for_input(const char *msg)
{
	char buf[32];

	fprintf(stderr, " * %s\n", msg);
	fprintf(stderr, " -- Press ENTER to continue ...");
	fgets(buf, 32, stdin);
}

int main(void)
{
	pid_t pid;
	int rc;
	int pipedes[2];

	rc = pipe(pipedes);
	DIE(rc < 0, "pipe");

	printf("pipedes[0] = %d; pipedes[1] = %d\n", pipedes[0], pipedes[1]);

	wait_for_input("pipe created");

	pid = fork();
	switch (pid) {
	case -1:  /* Fork failed, cleaning up. */
		/* TODO: Close both heads of the pipe. */
		DIE(pid, "fork");
		return EXIT_FAILURE;

	case 0:   /* Child process. */
		/* TODO: Close unused pipe head by child. */

		/* TODO: Call child loop and pass pipe head used for reading. */

		break;

	default:  /* Parent process. */
		/* TODO: Close unused pipe head by parent. */

		/* TODO: Call parent loop and pass pipe head used for writing. */

		/* Wait for child process to finish. */
		wait(NULL);

		break;
	}

	return 0;
}
