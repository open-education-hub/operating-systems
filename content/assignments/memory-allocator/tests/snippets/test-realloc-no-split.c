// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	int size;
	void *prealloc_ptr, *ptr, *dummy;

	size = 7120;
	prealloc_ptr = mock_preallocate();

	ptr = os_malloc(size);
	taint(ptr, size);
	dummy = os_malloc(1);

	/* Expect no split */
	for (unsigned int i = 0; i < METADATA_SIZE + 8; i++) {
		ptr = os_realloc_checked(ptr, size-i);

		/* If no split is performed, dummy always has the same addr */
		dummy = os_realloc_checked(dummy, 0);
		dummy = os_realloc_checked(dummy, 1);
	}

	/* Expect one split */
	ptr = os_realloc_checked(ptr, size - METADATA_SIZE - 8);
	dummy = os_realloc_checked(dummy, 0);
	dummy = os_realloc_checked(dummy, 1);

	os_realloc_checked(ptr, 0);
	os_realloc_checked(dummy, 0);
	os_realloc_checked(prealloc_ptr, 0);

	return 0;
}
