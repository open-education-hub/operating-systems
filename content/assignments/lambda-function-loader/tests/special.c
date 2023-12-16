// SPDX-License-Identifier: BSD-3-Clause

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter;

void run(void)
{
	srandom(time(NULL));

	/* Max 0.4 s */
	usleep((random() % 400000));

	/* Let's check how many times this we called this function. */
	counter++;
	printf("Got called %d times, cool!\n", counter);

	/* Max 0.4 s */
	usleep((random() % 400000));
}

void reset(void)
{
	/* Let's erase the history, shall we? */
	counter = 0;
	printf("Reseted the counter!\n");
}
