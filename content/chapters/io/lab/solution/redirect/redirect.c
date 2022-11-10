// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils/utils.h"

#define REDIRECT_FILE_NAME		"../../support/redirect/redirect_file.txt"

static void wait_for_input(const char *msg)
{
	char buf[32];

	fprintf(stderr, " * %s\n", msg);
	fprintf(stderr, " -- Press ENTER to continue ...");
	fgets(buf, 32, stdin);
}

static void do_redirect(int filedes, const char *filename)
{
	int rc;
	int fd;

	/**
	 * TODO 1: Refactor the code below to use `dup()` instead of
	 * `close()`-ing `filedes` and `open()`-ing the new file "on top" of
	 * the old file descriptor.
	 */
	/**
	 * fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	 * DIE(fd < 0, "open");
	 * 
	 * `close(filedes)` so that the `dup()` below copies `fd` into `filedes`.
	 * rc = close(filedes);
	 * DIE(rc < 0, "dup2");
	 *
	 * Copy `fd` into `filedes`.
	 * rc = dup(fd);
	 * DIE(rc < 0, "dup");
	 *
	 * Close the old `fd`. We already have it in `filedes`.
	 * rc = close(fd);
	 * DIE(rc < 0, "close");
	 */

	/**
	 * TODO 2: Refactor the code below to use `dup2()` instead of `close()`
	 * and `dup()`.
	 */

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

	/* `dup2()` closes the old `filedes` before replacing it with `fd`. */
	rc = dup2(fd, filedes);
	DIE(rc < 0, "dup2");

	rc = close(fd);
	DIE(rc < 0, "close");
}

int main(void)
{
	do_redirect(STDOUT_FILENO, REDIRECT_FILE_NAME);

	printf("Where did this messge disappear?\n");

	return 0;
}
