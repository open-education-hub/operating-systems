// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "./graded_test.h"

static void my_itoa(size_t num, char *a)
{
	unsigned char digit3;
	unsigned char digit2;
	unsigned char digit1;

	/* Print at most 3 decimal digits. */
	if (num > 999)
		num = 999;

	digit1 = num % 10;
	num /= 10;
	digit2 = num % 10;
	num /= 10;
	digit3 = num % 10;

	if (digit3 == 0)
		a[0] = ' ';
	else
		a[0] = '0' + digit3;

	if (digit2 == 0)
		a[1] = ' ';
	else
		a[1] = '0' + digit2;

	a[2] = '0' + digit1;
}

/*
 * Print test result. Printed message should fit in 72 characters.
 *
 * Print format is:
 *
 * description ...................... passed ... NNN
 * description ...................... failed ... NNN
 *   32 chars        24 chars           6     3   3
 */

static void print_test(const char *description, int result, size_t points)
{
	/* Make these global linkage, so it's only allocated once. */
	static char print_buffer[74];
	static const char failed[] = "failed";
	static const char passed[] = "passed";
	size_t i;
	size_t len;

	/* Collect description in print_buffer. */
	len = MIN(strlen(description), 32);
	for (i = 0; i < len; i++)
		print_buffer[i] = description[i];
	for (i = len; i < 32; i++)
		print_buffer[i] = ' ';
	print_buffer[32] = ' ';

	/* Collect dots in print_buffer. */
	for (i = 0; i < 24; i++)
		print_buffer[33+i] = '.';
	print_buffer[57] = ' ';

	/* Collect passed / failed. */
	for (i = 0; i < 6; i++) {
		if (result == 1)
			print_buffer[58+i] = passed[i];
		else
			print_buffer[58+i] = failed[i];
	}
	print_buffer[64] = ' ';

	/* Collect dots in print_buffer. */
	for (i = 0; i < 3; i++)
		print_buffer[65+i] = '.';
	print_buffer[68] = ' ';

	/* Collect number. */
	if (result == 1) {
		my_itoa(points, &print_buffer[69]);
	} else {
		print_buffer[69] = ' ';
		print_buffer[70] = ' ';
		print_buffer[71] = '0';
	}

	/* Collect newline. */
	print_buffer[72] = '\n';

	write(1, print_buffer, 73);
}

void run_test(struct graded_test *test)
{
	int res;

	res = test->function();
	print_test(test->description, res, test->points);
#ifdef EXIT_IF_FAIL
	exit(EXIT_FAILURE);
#endif
}

void run_tests(struct graded_test *tests, size_t count)
{
	size_t i;

	for (i = 0; i < count; i++)
		run_test(&tests[i]);
}
