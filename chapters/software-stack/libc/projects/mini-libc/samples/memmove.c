// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	/*
	 * dst and src do not overlap.
	 * dst should be set to "Let's test memmove against simple string!\n".
	 */
	char src[] = "Let's test memmove against simple string!\n";
	char dst[100];
	char str2[] = "memmove can be very useful......\n";

	memmove(dst, src, strlen(src));
	dst[strlen(src)] = '\0';

	write(1, dst, strlen(dst));

	/*
	 * dst and src overlap.
	 * dst should point to "memmove can be very useful.\n".
	 */
	memmove(str2 + 20, str2 + 15, 11);
	write(1, str2, strlen(str2));

	return 0;
}
