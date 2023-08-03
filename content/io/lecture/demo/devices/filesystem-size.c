/* SPDX-License-Identifier: BSD-3-Clause */

/*
 * Use ioctl to get number of bytes in filesystem.
 *
 * Some inspiration from Stack Overflow
 * https://stackoverflow.com/questions/1960421/how-can-i-determine-the-space-size-of-my-drive-programatically-both-in-linux-an
 */

#include <fcntl.h>
#include <linux/fs.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "utils/utils.h"

#define SIZE_UNIT (1024UL * 1024 * 1024)  /* 1GB */

int main(int argc, const char *argv[])
{
	int fd;
	unsigned long long numblocks = 0;
	int rc;

	if (argc < 2) {
		printf("Usage: %s partition_path\n", argv[0]);
		return 0;
	}

	fd = open(argv[1], O_RDONLY);
	DIE(fd < 0, "open");

	rc = ioctl(fd, BLKGETSIZE64, &numblocks);
	DIE(rc < 0, "ioctl");

	printf("Total space %.3f GB\n", (double)numblocks / SIZE_UNIT);

	close(fd);
	return 0;
}

