// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr, *prealloc_ptr;

	prealloc_ptr = mock_preallocate();

	/* Expand last block */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptr = os_calloc_checked(1, inc_sz_sm[i]);
		os_free(ptr);
	}

	/* Cleanup */
	os_free(prealloc_ptr);

	return 0;
}
