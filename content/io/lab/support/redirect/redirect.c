// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils/utils.h"

#define REDIRECT_FILE_NAME		"redirect_file.txt"

static void wait_for_input(const char *func_name, const char *msg)
{
	char buf[32];

	fprintf(stderr, " * %s(): %s\n", func_name, msg);
	fprintf(stderr, " -- Press ENTER to continue ...");
	fgets(buf, 32, stdin);
}

static void do_redirect(int file_des, const char *filename)
{
	int rc;
	int fd;

	/**
	 * TODO 1: Refactor the code below to use `dup()` instead of
	 * `close()`-ing `file_des` and `open()`-ing the new file "on top" of
	 * the old file descriptor.
	 */

	/**
	 * TODO 2: Refactor the code below to use `dup2()` instead of `close()`
	 * and `dup()`.
	 */

	wait_for_input(__func__, "before closing `file_des`");

	/**
	 *`close()` `stdout` so that the file descriptor created below is 1,
	 * thus "replacing" `stdout`.
	 */
	rc = close(file_des);
	DIE(rc < 0, "close");

	wait_for_input(__func__, "after closing `file_des`");

	/* The first available file descriptor is 1 (`stdout`). */
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

	wait_for_input(__func__, "after opening `filename`");
}

int main(void)
{
	do_redirect(STDOUT_FILENO, REDIRECT_FILE_NAME);

	printf("Where did this messge disappear?\n");

	return 0;
}
