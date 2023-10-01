// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr;

	ptr = os_realloc_checked(NULL, 2 * MMAP_THRESHOLD);
	ptr = os_realloc_checked(ptr, 1986);
	os_free(ptr);

	return 0;
}
