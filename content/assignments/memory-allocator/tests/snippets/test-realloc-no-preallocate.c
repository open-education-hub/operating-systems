// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr;

	ptr = os_realloc_checked(NULL, 0);
	ptr = os_realloc_checked(ptr, MMAP_THRESHOLD);
	os_free(ptr);

	return 0;
}
