// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <internal/types.h>
#include <sys/stat.h>
#include <string.h>

#define EXISTENT_FILE "./existent_file"

static char *itoa(long i, char *b)
{
	char const digit[] = "0123456789";
	char *p = b;
	long shifter = i;

	do {
		++p;
		shifter = shifter / 10;
	} while (shifter);

	*p = '\0';
	do {
		*--p = digit[i % 10];
		i = i / 10;
	} while (i);

	return b;
}

static void reset_buffer(char *buf, int len)
{
	int i;

	for (i = 0; i < len; i++)
		buf[i] = '\0';
}

/* Call fstat on regular file and print file characteristics. */
int main(void)
{
	int fd;
	struct stat s;
	int r;
	char number[20];

	fd = open(EXISTENT_FILE, 0, 0);
	if (fd < 0)
		exit(EXIT_FAILURE);

	r = fstat(fd, &s);
	if (r < 0)
		exit(EXIT_FAILURE);

	/* File type is regular */
	if ((s.st_mode & __S_IFMT) != __S_IFREG)
		exit(EXIT_FAILURE);

	/* Print inode number */
	reset_buffer(number, 20);

	itoa((unsigned long)(s.st_ino), number);
	write(1, number, strlen(number));
	write(1, " ", 1);

	/* Print UID */
	reset_buffer(number, 20);

	itoa((long) (s.st_uid), number);
	write(1, number, strlen(number));
	write(1, " ", 1);

	/* Print GID */
	reset_buffer(number, 20);

	itoa((long) (s.st_gid), number);
	write(1, number, strlen(number));
	write(1, " ", 1);

	/* Print number of links */
	reset_buffer(number, 20);

	itoa((long) (s.st_nlink), number);
	write(1, number, strlen(number));
	write(1, " ", 1);

	/* Print number of blocks */
	reset_buffer(number, 20);

	itoa((long) (s.st_blocks), number);
	write(1, number, strlen(number));
	write(1, " ", 1);

	/* Print file size */
	reset_buffer(number, 20);

	itoa((long) (s.st_size), number);
	write(1, number, strlen(number));
	write(1, " ", 1);

	/* Print last modify time */
	reset_buffer(number, 20);

	itoa((long) (s.st_mtime), number);
	write(1, number, strlen(number));
	write(1, "\n", 1);

	r = close(fd);
	if (r < 0)
		exit(EXIT_FAILURE);

	return 0;
}
