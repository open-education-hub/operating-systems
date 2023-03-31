// SPDX-License-Identifier: BSD-3-Clause
#include <stdio.h>

// function that does nothing
void func(void) {}

int main(void)
{
	printf("User function address: %p\n", &func);
	printf("Library function address: %p\n", &printf);

	return 0;
}
