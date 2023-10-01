// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptr, *ptrs[NUM_SZ_SM];

	prealloc_ptr = mock_preallocate();
	os_free(prealloc_ptr);

	/* Initialize blocks */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptrs[i] = os_realloc_checked(NULL, inc_sz_sm[i]);
		taint(ptrs[i], inc_sz_sm[i]);
	}

	/* Test blocks coalesce on the first 2 block */
	os_free(ptrs[0]);
	os_free(ptrs[1]);
	ptrs[0] = os_realloc_checked(NULL, inc_sz_sm[0] + inc_sz_sm[1]);

	/* Test realloc expand on the first 2 block */
	os_free(ptrs[0]);
	ptrs[0] = os_realloc_checked(NULL, inc_sz_sm[0]);
	ptrs[0] = os_realloc_checked(ptrs[0], inc_sz_sm[0] + inc_sz_sm[1]);

	/* Test blocks coalesce on the middle 2 block */
	os_free(ptrs[4]);
	os_free(ptrs[5]);
	ptrs[4] = os_realloc_checked(NULL, inc_sz_sm[4] + inc_sz_sm[5]);

	/* Test realloc expand on the middle 2 block */
	os_free(ptrs[4]);
	ptrs[4] = os_realloc_checked(NULL, inc_sz_sm[4]);
	ptrs[4] = os_realloc_checked(ptrs[4], inc_sz_sm[4] + inc_sz_sm[5]);

	/* Test blocks coalesce on the last 2 block */
	os_free(ptrs[8]);
	os_free(ptrs[9]);
	ptrs[8] = os_realloc_checked(NULL, inc_sz_sm[8] + inc_sz_sm[9]);

	/* Test realloc expand on the last 2 block */
	os_free(ptrs[8]);
	ptrs[8] = os_realloc_checked(NULL, inc_sz_sm[8]);
	ptrs[8] = os_realloc_checked(ptrs[8], inc_sz_sm[8] + inc_sz_sm[9]);

	/* Expect new block  */
	ptr = os_realloc_checked(NULL, 3000);
	os_free(ptr);

	/* Cleanup */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		if (i == 1 || i == 5 || i == 9)
			continue;
		os_free(ptrs[i]);
	}

	return 0;
}
