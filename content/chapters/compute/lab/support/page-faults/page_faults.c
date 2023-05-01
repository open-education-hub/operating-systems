// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include "utils/utils.h"

int main(void)
{
	char *a, *b;
	char filename[] = "file.txt";
	int fd;
	struct stat filestat;
	char *data;

	getchar();

	printf("Press enter to allocate 100 Bytes\n");
	getchar();

	a = malloc(100);
	DIE(a == NULL, "malloc");

	printf("Press enter to allocate 1GB\n");
	getchar();

	b = malloc(1 * 1024 * 1024 * 1024);
	DIE(b == NULL, "malloc");

	printf("Press enter to write a[50]\n");
	getchar();

	a[50] = 1;

	printf("Press enter to write every byte in b\n");
	getchar();

	for (int i = 0; i < 1 * 1024 * 1024 * 1024; i++)
		b[i] = 0;

	printf("Press enter to free a and b\n");
	getchar();

	free(a);
	free(b);

	printf("Press enter to open \"file.txt\"\n");
	getchar();

	fd = open(filename, O_RDONLY);
	DIE(fd < 0, "open");

	printf("Press enter to get file size\n");
	getchar();

	DIE(fstat(fd, &filestat) != 0, "fstat");
	DIE(posix_fadvise(fd, 0, filestat.st_size, POSIX_FADV_DONTNEED) != 0, "posix_fadvise");


	printf("Press enter to map file into memory\n");
	getchar();

	data = mmap(NULL, filestat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	DIE(data == MAP_FAILED, "mmap");

	printf("Press enter to print file contents\n");
	getchar();

	printf("%s\n", data);

	printf("Press enter to close file\n");
	getchar();

	munmap(data, filestat.st_size);
	close(fd);

	printf("Press enter to exit\n");
	getchar();

	return 0;
}
