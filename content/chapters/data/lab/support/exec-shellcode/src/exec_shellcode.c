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
	/* TODO: Create mapping to fit the shellcode. */
}

static void read_shellcode(const char * const fname)
{
	/* TODO: Read content from file in shellcode. */
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
