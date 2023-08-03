/* SPDX-License-Identifier: BSD-3-Clause */

#include <unistd.h>

int main(void)
{
	char buffer[128];
	ssize_t nread;

	write(1, "Hello, world!\n", 14);
	write(1, "Bye, world!\n", 12);

	nread = read(0, buffer, 128);
	if (nread > 0)
		write(1, buffer, nread);

	pause();

	return 0;
}
