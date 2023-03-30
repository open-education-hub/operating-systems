// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	int size;
	void *prealloc_ptr, *ptr, *dummy;

	size = 3024;
	prealloc_ptr = mock_preallocate();

	ptr = os_calloc_checked(size, 1);
	dummy = os_calloc_checked(1, 1);

	/* Expect no split */
	for (unsigned int i = 0; i < METADATA_SIZE + 8; i++) {
		os_free(ptr);
		ptr = os_calloc_checked(size-i, 1);

		/* If no split is performed, dummy always has the same addr */
		os_free(dummy);
		dummy = os_calloc_checked(1, 1);
	}

	/* Expect one split */
	os_free(ptr);
	ptr = os_calloc_checked(size - METADATA_SIZE - 8, 1);
	os_free(dummy);
	dummy = os_calloc_checked(1, 1);

	/* Cleanup */
	os_free(ptr);
	os_free(dummy);
	os_free(prealloc_ptr);

	return 0;
}
