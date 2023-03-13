/* SPDX-License-Identifier: BSD-3-Clause */

#include "./string.h"
#include "./syscall.h"

static const char src[] = "warhammer40k\n";
static char dest[128];

int main(void) {
	strcpy(dest, src);

	write(1, "Destination string is: ", 23);
	write(1, dest, strlen(dest));

	exit(0);
	return 0;
}
