/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "utils/utils.h"

#define BUFSIZE		1024

static char buffer[BUFSIZE] = { '1' };

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
	ssize_t n;
	int ret;

	wait_for_input("Open f.txt");
	fd = open("f.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

    wait_for_input("Write 1024 bytes");
	n = write(fd, buffer, BUFSIZE);
	DIE(n < 0, "write");

    wait_for_input("Go backwards 512 bytes");
	n = lseek(fd, -512, SEEK_CUR);
	DIE(n < 0, "lseek");

	wait_for_input("Read 256 bytes");
	n = read(fd, buffer, 256);
	DIE(n < 0, "read");

    wait_for_input("Truncate to 256 bytes");
    ret = ftruncate(fd, 256);
	DIE(ret < 0, "ftruncate");

    wait_for_input("Close file");
	ret = close(fd);
    DIE(ret < 0, "close");

	return 0;
}
