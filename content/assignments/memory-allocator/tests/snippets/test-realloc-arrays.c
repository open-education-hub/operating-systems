// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptr_free, *ptrs[NUM_SZ_SM];

	prealloc_ptr = mock_preallocate();

	/* Test small allocations */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptrs[i] = os_realloc_checked(NULL, inc_sz_sm[i]);
		taint(ptrs[i], inc_sz_sm[i]);
	}

	/* Test block truncating on small allocations */
	for (int i = 1; i < NUM_SZ_SM; i++)
		ptrs[i] = os_realloc_checked(ptrs[i], inc_sz_sm[i-1]);

	/* Test block expansion on small allocations */
	for (int i = 0; i < NUM_SZ_SM; i++)
		ptrs[i] = os_realloc_checked(ptrs[i], inc_sz_sm[i]);

	/* Test mapped reallocations */
	for (int i = 0; i < NUM_SZ_LG; i++)
		ptrs[i] = os_realloc_checked(ptrs[i], inc_sz_lg[i]);

	/* Test mixed reallocations */
	for (int i = 0; i < NUM_SZ_MD; i++)
		ptrs[i] = os_realloc_checked(ptrs[i], inc_sz_md[i]);

	/* Test realloc on free block */
	ptr_free = os_realloc_checked(NULL, 100);
	os_free(ptr_free);
	os_realloc_checked(ptr_free, 200);

	/* Cleanup using realloc */
	os_realloc_checked(prealloc_ptr, 0);
	for (int i = 0; i < NUM_SZ_SM; i++)
		os_realloc_checked(ptrs[i], 0);

	return 0;
}
