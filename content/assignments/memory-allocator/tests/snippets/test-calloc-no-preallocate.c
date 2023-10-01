// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr;

	ptr = os_calloc_checked(0, 100);
	os_free(ptr);
	ptr = os_calloc_checked(100, 0);
	os_free(ptr);
	ptr = os_calloc_checked(4080, 1);
	os_free(ptr);
	ptr = os_calloc_checked(1, MMAP_THRESHOLD);
	os_free(ptr);

	return 0;
}
