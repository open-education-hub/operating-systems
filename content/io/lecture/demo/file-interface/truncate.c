/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils/utils.h"

#define FILENAME		    "fake-gargantua.dat"
#define SIZE_TO_TRUNCATE	(10*2048UL*1024*1024)	/* 20GB */

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
	struct stat sbuf;

    wait_for_input("Open an empty file for writting");
	fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

    wait_for_input("Use truncate to update the file length to 20GB");
	ret = ftruncate(fd, SIZE_TO_TRUNCATE);
	DIE(ret < 0, "ftruncate");

    wait_for_input("Use fstat to read file information");
	ret = fstat(fd, &sbuf);
	DIE(ret < 0, "ftruncate");

	printf("file size is: %ld\n", sbuf.st_size);
	printf("number of blocks is: %ld\n", sbuf.st_blocks);

    wait_for_input("Close file");
    ret = close(fd);
    DIE(ret < 0, "close");

	return 0;
}
