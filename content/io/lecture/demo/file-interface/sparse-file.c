/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils/utils.h"

#define FILENAME	    "sparse.dat"

static char buffer[1024];

static void
wait_for_input(const char *msg)
{
    char buf[32];

    printf(" * %s\n", msg);
    printf(" -- Press ENTER to continue ...\n");
    fflush(stdout);
    fgets(buf, 32, stdin);
}

int main(void)
{
	int fd;
	int ret;

	memset(buffer, 'A', 1024);

    wait_for_input("Open an empty file for writting");
	fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

    wait_for_input("Write 1024 bytes");
	ret = write(fd, buffer, 1024);
	DIE(ret < 0, "write");

    wait_for_input("Move 1024 bytes past the end of the file");
	ret = lseek(fd, 1024, SEEK_END);
	DIE(ret < 0, "lseek");

    wait_for_input("Write 1024 bytes");
	ret = write(fd, buffer, 1024);
	DIE(ret < 0, "write");

    wait_for_input("Move 1024 bytes past the end of the file");
	ret = lseek(fd, 1024, SEEK_END);
	DIE(ret < 0, "lseek");

    wait_for_input("Write 1024 bytes");
	ret = write(fd, buffer, 1024);
	DIE(ret < 0, "write");

    wait_for_input("Close file");
    ret = close(fd);
    DIE(ret < 0, "close");

	return 0;
}
