// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "utils/utils.h"

#define DIR_NAME	"../simple-file-operations/dir"

static void open_directory(const char *dir_name)
{
	int fd;

	fd = open(dir_name, O_DIRECTORY, 0755);
	DIE(fd < 0, "open");

	printf("Directory file descriptor is: %d\n", fd);
}

int main(void)
{
	open_directory(DIR_NAME);
	return 0;
}
