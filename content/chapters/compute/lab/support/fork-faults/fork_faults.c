/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "utils/utils.h"

#define NUM_PAGES	1024

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Press ENTER to continue ..."); fflush(stdout);
	fgets(buf, 32, stdin);
}

int main(void)
{
	char *p;
	int status;
	size_t i;
	int page_size = getpagesize();
	char value;

	wait_for_input("Start program");

	p = mmap(NULL, NUM_PAGES * page_size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(p == MAP_FAILED, "mmap");

	wait_for_input("1. Pages allocated");

	for (i = 0; i < NUM_PAGES; i++)
		p[i * page_size] = i;

	wait_for_input("2. Allocate frames for pages");

	switch (fork()) {
		case -1:    /* Handle error */
			DIE(1, "fork");
			break;

		case 0:     /* Child process */
			wait_for_input("3. Child process begins");

			for (i = 0; i < NUM_PAGES / 2; i++)
				value = p[i * page_size];
			wait_for_input("4. Child process after reading");

			for (i = NUM_PAGES / 2; i < NUM_PAGES; i++)
				p[i * page_size] = page_size - i;
			wait_for_input("5. Child process after writing");

			exit(EXIT_SUCCESS);
			break;

		default:    /* Parent process */
			break;
	}

	(void)value;

	wait(&status);
	wait_for_input("6. Parent process after waiting for child");

	for (i = 0; i < NUM_PAGES; i++)
		p[i * page_size] = i;

	wait_for_input("7. Parent ending");

	return 0;
}
