// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>

int main(void)
{
	write(1, "Hello, World!\n", 14);

	return 0;
}
