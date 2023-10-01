// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr;

	ptr = os_malloc_checked(0);
	os_free(ptr);
	ptr = os_malloc_checked(MMAP_THRESHOLD);
	os_free(ptr);

	return 0;
}
