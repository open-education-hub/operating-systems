/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>

#include "utils/utils.h"

#define NUM_STEPS	10
#define ALLOC_SIZE_KB	64
#define ALLOC_SIZE	(ALLOC_SIZE_KB * 1024)

static void wait_for_input(const char *msg)
{
	char buffer[128];

	printf("%s ...", msg);
	fgets(buffer, 128, stdin);
}

int main(void)
{
	size_t i;
	void *p;

	wait_for_input("Press key to allocate");

	for (i = 0; i < NUM_STEPS; i++) {
		p = malloc(ALLOC_SIZE);
		DIE(p == NULL, "malloc");
		printf("New allocation at %p\n", p);
	}

	wait_for_input("Press key to deallocate");

	free(p);

	wait_for_input("Press key to close the program");

	return 0;
}
