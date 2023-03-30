// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr;

	ptr = os_calloc_checked(1986, 2);
	os_free(ptr);

	return 0;
}
