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

#define FS_PATH  "/dev/nvme0n1p5"
#define SIZE_UNIT (1024UL * 1024 * 1024)  /* 1GB */

int main(void)
{
	int fd;
	unsigned long long numblocks = 0;
	int rc;

	fd = open(FS_PATH, O_RDONLY);
	DIE(fd < 0, "open");

	rc = ioctl(fd, BLKGETSIZE64, &numblocks);
	DIE(rc < 0, "ioctl");

	printf("Total space %.3f GB\n", (double)numblocks / SIZE_UNIT);

	close(fd);
	return 0;
}

