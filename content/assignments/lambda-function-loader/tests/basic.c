// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void run(void)
{
	printf("%s\n", __func__);
}

void cat(const char *filename)
{
	int fd;
	char buf[1024];
	int read_bytes;

	fd = open(filename, O_RDONLY);

	while ((read_bytes = read(fd, buf, sizeof(buf))) > 0)
		write(STDOUT_FILENO, buf, read_bytes);
}
