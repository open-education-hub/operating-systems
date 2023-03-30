// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	int size;
	void *prealloc_ptr, *ptr, *dummy;

	size = 7120;
	prealloc_ptr = mock_preallocate();

	ptr = os_malloc_checked(size);
	dummy = os_malloc_checked(1);

	/* Expect no split */
	for (unsigned int i = 0; i < METADATA_SIZE + 8; i++) {
		os_free(ptr);
		ptr = os_malloc_checked(size-i);

		/* If no split is performed, dummy always has the same addr */
		os_free(dummy);
		dummy = os_malloc_checked(1);
	}

	/* Expect one split */
	os_free(ptr);
	ptr = os_malloc_checked(size - METADATA_SIZE - 8);
	os_free(dummy);
	dummy = os_malloc_checked(1);

	/* Cleanup */
	os_free(ptr);
	os_free(dummy);
	os_free(prealloc_ptr);

	return 0;
}
