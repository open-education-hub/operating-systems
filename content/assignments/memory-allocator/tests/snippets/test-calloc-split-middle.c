// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptr, *ptr1, *ptr2, *ptr3;
	void *c1, *c2, *c3, *c4, *c5, *c6;

	prealloc_ptr = mock_preallocate();

	ptr1 = os_calloc_checked(20, 50);
	ptr2 = os_calloc_checked(20, 50);
	taint(ptr2, 1000);
	ptr3 = os_calloc_checked(20, 50);

	/* Split the middle block in 3 chunks */
	os_free(ptr2);
	c1 = os_calloc_checked(30, 10);
	c2 = os_calloc_checked(30, 10);
	taint(c2, 300);
	c3 = os_calloc_checked(30, 10);

	/* Split the middle block in 3 chunks */
	os_free(c2);
	c4 = os_calloc_checked(14, 5);
	c5 = os_calloc_checked(14, 5);
	c6 = os_calloc_checked(14, 5);

	/* Expect new block  */
	ptr = os_calloc_checked(1, 2000);
	os_free(ptr);

	/* Cleanup */
	os_free(prealloc_ptr);
	os_free(ptr1);
	os_free(ptr3);
	os_free(c1);
	os_free(c3);
	os_free(c4);
	os_free(c5);
	os_free(c6);

	return 0;
}
