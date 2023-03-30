// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	int i;
	void *ptrs1[NUM_SZ_SM];
	void *ptrs2[NUM_SZ_SM];
	void *ptrs3[NUM_SZ_SM];
	void *ptrs4[NUM_SZ_MD];
	void *ptrs5[NUM_SZ_LG];
	void *prealloc_ptr;

	prealloc_ptr = mock_preallocate();

	/* Test small allocations incremental */
	for (i = 0; i < NUM_SZ_SM; i++)
		ptrs1[i] = os_calloc_checked(1, inc_sz_sm[i]);

	/* Test small allocations decremental */
	for (i = 0; i < NUM_SZ_SM; i++)
		ptrs2[i] = os_calloc_checked(1, dec_sz_sm[i]);

	/* Test small allocations alternative */
	for (i = 0; i < NUM_SZ_SM; i++)
		ptrs3[i] = os_calloc_checked(1, alt_sz_sm[i]);

	/* Test medium allocations */
	for (i = 0; i < NUM_SZ_MD; i++)
		ptrs4[i] = os_calloc_checked(1, inc_sz_md[i]);

	/* Test large allocations */
	for (i = 0; i < NUM_SZ_LG; i++)
		ptrs5[i] = os_calloc_checked(1, inc_sz_lg[i]);

	/* Cleanup */
	os_free(prealloc_ptr);
	for (i = 0; i < NUM_SZ_SM; i++) {
		os_free(ptrs1[i]);
		os_free(ptrs2[i]);
		os_free(ptrs3[i]);
	}
	for (i = 0; i < NUM_SZ_MD; i++)
		os_free(ptrs4[i]);

	for (i = 0; i < NUM_SZ_LG; i++)
		os_free(ptrs5[i]);

	return 0;
}
