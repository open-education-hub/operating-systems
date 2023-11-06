// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include "utils.h"

static void *shellcode_mapping;

static void usage(const char * const argv0)
{
	fprintf(stderr, "Usage: %s shellcode_file\n", argv0);
}

static void create_shellcode_mapping(void)
{
	/* TODO 4: Create mapping to fit the shellcode. */
	shellcode_mapping = mmap(NULL, sysconf(_SC_PAGESIZE),
			PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	DIE(shellcode_mapping == MAP_FAILED, "mmap");
}

static void read_shellcode(const char * const fname)
{
	/* TODO 8: Read content from file in shellcode. */
	FILE *f;

	f = fopen(fname, "rb");
	DIE(f == NULL, "fopen");

	fread(shellcode_mapping, sysconf(_SC_PAGESIZE), 1, f);

	fclose(f);
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	create_shellcode_mapping();
	read_shellcode(argv[1]);

	((void (*)(void)) shellcode_mapping)();

	return 0;
}
