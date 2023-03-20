// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <string.h>

void isEqual(int ret_code)
{
	if (ret_code == 0)
		write(1, "Equal\n", 6);
	else if (ret_code == -1)
		write(1, "Lower\n", 6);
	else if (ret_code == 1)
		write(1, "Higher\n", 7);
}

int main(void)
{
	int ret = 0;

	/* equal */
	ret = memcmp("abc", "abc", 3);
	isEqual(ret);

	/* equal */
	ret = memcmp("abcd", "abca", 3);
	isEqual(ret);

	/* higher */
	ret = memcmp("bca", "abc", 3);
	isEqual(ret);

	return 0;
}
