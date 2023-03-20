// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <string.h>

int main(void)
{
	/*
	 * Search for the first index of "simple" in "This is a simple string".
	 * pch should point to "simple string".
	 */
	char str[] = "This is a simple string";
	char *pch;
	char string[] = "This is a test string for testing";
	char *p;

	pch = strstr(str, "simple");
	if (pch != NULL) {
		write(1, pch, strlen(pch));
		write(1, "\n", 1);
	}

	/*
	 * Search for the last index of "test" in "This is a test string for testing".
	 * pch should point to "testing.
	 */
	p = strrstr(string, "test");
	if (p != NULL) {
		write(1, p, strlen(p));
		write(1, "\n", 1);
	}

	return 0;
}
