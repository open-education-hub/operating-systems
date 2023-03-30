// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr, *prealloc_ptr;

	prealloc_ptr = mock_preallocate();
	ptr = os_malloc(inc_sz_sm[0]);
	taint(ptr, inc_sz_sm[0]);

	/* Expand last block */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptr = os_realloc_checked(ptr, inc_sz_sm[i]);
		taint(ptr, inc_sz_sm[i]);
	}

	/* Cleanup */
	os_realloc_checked(ptr, 0);
	os_realloc_checked(prealloc_ptr, 0);

	return 0;
}
