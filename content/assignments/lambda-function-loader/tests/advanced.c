// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run(void)
{
	printf("hello from advanced\n");
}

void clumsy(void)
{
	int *seg = NULL;
	int fault = 42;

	printf("How do pointers work?\n");

	*seg = fault;
}

void going_to_sleep(void)
{
	printf("I don't feel so good, I'm going to sleep for good.\n");
	exit(1);
}

void sleepy(void)
{
	printf("Will go to sleep\n");
	usleep(500000);
	printf("I love the smell of napalm in the morning\n");
}
