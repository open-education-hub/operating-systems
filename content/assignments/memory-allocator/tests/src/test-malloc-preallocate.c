// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr;

	ptr = os_malloc_checked(1986);
	os_free(ptr);

	return 0;
}
