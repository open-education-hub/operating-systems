/* SPDX-License-Identifier: BSD-3-Clause */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "utils/utils.h"

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Press ENTER to continue ...");
	fflush(stdout);
	fgets(buf, 32, stdin);
}

int main(int argc, char *argv[])
{
	int fdin;
	int fdout;
	int rc;
	char *src;
	char *dst;
	struct stat statbuf;

	DIE(argc != 3, "Usage: ./mmap_cp <from_file> <to_file>");

	/* TODO: Open the input file. */
	fdin = open(argv[1], O_RDONLY);
	DIE(fdin == -1, "open fdin");

	/* TODO: Open/create the output file. */
	fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	DIE(fdout == -1, "open fdout");

	/**
	 * TODO: Truncate the output file to the input file size. Use `fstat()`
	 * to get the size of the input file and `ftruncate()` to set the size
	 * of the output file.
	 */
	rc = fstat(fdin, &statbuf);
	DIE(rc == -1, "fstat");

	rc = ftruncate(fdout, statbuf.st_size);
	DIE(rc == -1, "ftruncate");

	/* TODO: `mmap()` the input file. */
	src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);
	DIE(src == MAP_FAILED, "mmap src");

	// wait_for_input("Mapped input file.");

	/* TODO: `mmap()` the output file. */
	dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			   fdout, 0);
	DIE(dst == MAP_FAILED, "mmap dst");

	// wait_for_input("Mapped output file.");

	/**
	 * TODO: Copy the contents of the input mapping to the output mapping.
	 */
	memcpy(dst, src, statbuf.st_size);

	/* TODO: Clean up. Use `munmap()` to unmap the 2 files. */
	rc = munmap(src, statbuf.st_size);
	DIE(rc == -1, "munmap source");

	rc = munmap(dst, statbuf.st_size);
	DIE(rc == -1, "munmap dest");

	rc = close(fdin);
	DIE(rc == -1, "close source");

	rc = close(fdout);
	DIE(rc == -1, "close dest");

	return 0;
}
