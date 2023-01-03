/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils/utils.h"

#define MAX_LINE_SIZE		256
#define MAX_ARGS		8

#define ERROR			0
#define SIMPLE			1
#define REDIRECT		2
#define PIPE			3
#define SHELL_EXIT		4

static char *verb;
static char **args;
static char *stdin_file;
static char *stdout_file;
static char *stderr_file;

static int parse_line(char *line);
static void alloc_mem(void);
static void free_mem(void);

static void do_redirect(int filedes, const char *filename)
{
	int rc;
	int fd;

	/* TODO: Redirect `filedes` into `fd` representing `filename`. */
}

static void simple_cmd(char **args)
{
	pid_t pid;
	pid_t wait_ret;
	int status;

	/**
	 * Create a process to execute the command. Use `execvp` to launch the
	 * new process.
	 */
	pid = fork();
	switch (pid) {
	case -1:
		/* Error */
		DIE(1, "fork");
		break;

	case 0:
		/* Child process */

		/**
		 * TODO: Call `do_redirect()`. Assume the only file descriptor
		 * that needs to be redirected is `stdout`. Its file descriptor
		 * is `STDOUT_FILENO`.
		 */
		if (stdout_file != NULL)
			do_redirect(STDOUT_FILENO, stdout_file);

		execvp(args[0], (char *const *) args);
		DIE(1, "execvp");
		break;

	default:
		/* Parent process */
		wait_ret = waitpid(pid, &status, 0);
		DIE(wait_ret < 0, "waitpid");

		if (WIFEXITED(status))
			printf("Child process (pid %d) terminated normally, "
					"with exit code %d\n",
					pid, WEXITSTATUS(status));
	}
}

int main(void)
{
	int type;
	char line[MAX_LINE_SIZE];

	alloc_mem();

	while (1) {
		printf("> ");
		fflush(stdout);

		memset(line, 0, MAX_LINE_SIZE);

		if (fgets(line, sizeof(line), stdin) == NULL) {
			free_mem();
			exit(EXIT_SUCCESS);
		}

		type = parse_line(line);

		switch (type) {
		case SHELL_EXIT:
			free_mem();
			exit(EXIT_SUCCESS);

		case SIMPLE:
			simple_cmd(args);
			break;
		}
	}

	return 0;
}

static void alloc_mem(void)
{
	args = malloc(MAX_ARGS * sizeof(char *));
	DIE(args == NULL, "malloc");
}

static void free_mem(void)
{
	free(args);
}

static int parse_line(char *line)
{
	int ret = SIMPLE;
	int idx = 0;
	char *token;
	char *delim = "=\n";

	stdin_file = NULL;
	stdout_file = NULL;
	stderr_file = NULL;

	/* Check for exit. */
	if (strncmp("exit", line, strlen("exit")) == 0)
		return SHELL_EXIT;

	/* Regular command. */
	delim = " \t\n";
	token = strtok_r(line, delim);

	if (token == NULL)
		return ERROR;

	verb = strdup(token);

	/* Copy args. */
	while (token != NULL) {
		if (token == NULL) {
			printf(" Expansion failed\n");
			return ERROR;
		}

		if (strncmp(token, ">", strlen(">")) == 0) {
			if (strlen(token) > strlen(">")) {
				token++;
				stdout_file = strdup(token);
			} else {
				token = strtok_r(NULL, delim);
				stdout_file = strdup(token);
			}
		} else {
			args[idx++] = strdup(token);
		}

		token = strtok_r(NULL, delim);
	}

	args[idx++] = NULL;
	return ret;
}
