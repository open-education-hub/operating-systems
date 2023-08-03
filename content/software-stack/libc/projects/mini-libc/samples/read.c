// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char buffer[128];
	int n;

	n = read(0, buffer, 128);
	if (n < 0)
		exit(EXIT_FAILURE);

	write(1, buffer, n);

	return 0;
}
