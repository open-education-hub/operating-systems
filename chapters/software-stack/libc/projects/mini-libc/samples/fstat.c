// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <internal/types.h>

#define FILENAME	"./file"

static char *itoa(long i, char *b)
{
	char const digit[] = "0123456789";
	char *p = b;
	int shifter = i;

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

int main(void)
{
	int fd;
	struct stat s;
	char number[20];
	int r;

	memset(&s, 0, sizeof(s));

	/* Create regular file with RW permissions for current user */
	fd = open(FILENAME, O_CREAT | O_RDWR, S_IRUSR);
	if (fd < 0) {
		write(1, "Something went wrong - create file.\n", strlen("Something went wrong - create file.\n"));
		return -1;
	}

	/* Call fstat and populate the stat structure */
	r = fstat(fd, &s);
	if (r != 0) {
		write(1, "Something went wrong - fstat.\n", strlen("Something went wrong - fstat.\n"));
		return -1;
	}

	/* Print file type */
	switch (s.st_mode & __S_IFMT) {
	case __S_IFBLK:
		write(1, "block device\n", strlen("block device\n"));
		break;
	case __S_IFCHR:
		write(1, "character device\n", strlen("character device\n"));
		break;
	case __S_IFDIR:
		write(1, "directory\n", strlen("directory\n"));
		break;
	case __S_IFIFO:
		write(1, "FIFO/pipe\n", strlen("FIFO/pipe\n"));
		break;
	case __S_IFLNK:
		write(1, "symlink\n", strlen("symlink\n"));
		break;
	case __S_IFREG:
		write(1, "regular file\n", strlen("regular file\n"));
		break;
	case __S_IFSOCK:
		write(1, "socket\n", strlen("socket\n"));
		break;
	default:
		write(1, "unknown?\n", strlen("unknown?\n"));
		break;
	}

	/* Print inode number */
	itoa((long) (s.st_ino), number);
	write(1, "INO: ", strlen("INO: "));
	write(1, number, strlen(number));
	write(1, "\n", 1);

	/* Print UID */
	memset(number, 0, sizeof(number));
	itoa((long) (s.st_uid), number);
	write(1, "UID: ", strlen("UID: "));
	write(1, number, strlen(number));
	write(1, "\n", 1);

	/* Print GID */
	memset(number, 0, sizeof(number));
	itoa((long) (s.st_gid), number);
	write(1, "GID: ", strlen("GID: "));
	write(1, number, strlen(number));
	write(1, "\n", 1);

	/* Print number of links */
	memset(number, 0, sizeof(number));
	itoa((long) (s.st_nlink), number);
	write(1, "Number of links: ", strlen("Number of links: "));
	write(1, number, strlen(number));
	write(1, "\n", 1);

	/* Print block size */
	memset(number, 0, sizeof(number));
	itoa((long) (s.st_blksize), number);
	write(1, "Block size: ", strlen("Block size: "));
	write(1, number, strlen(number));
	write(1, "\n", 1);

	/* Print number of blocks */
	memset(number, 0, sizeof(number));
	itoa((long) (s.st_blocks), number);
	write(1, "Number of blocks: ", strlen("Number of blocks: "));
	write(1, number, strlen(number));
	write(1, "\n", 1);

	/* Print file size */
	memset(number, 0, sizeof(number));
	itoa((long) (s.st_size), number);
	write(1, "File size: ", strlen("File size: "));
	write(1, number, strlen(number));
	write(1, "\n", 1);

	/* Print last modify time */
	memset(number, 0, sizeof(number));
	itoa((long) (s.st_mtime), number);
	write(1, "Last modify time: ", strlen("Last modify time: "));
	write(1, number, strlen(number));
	write(1, "\n", 1);
	write(1, "\n", 1);

	/* Close file */
	r = close(fd);
	if (r < 0)
		write(1, "Something went wrong - close.\n", strlen("Something went wrong - close.\n"));

	return 0;
}
