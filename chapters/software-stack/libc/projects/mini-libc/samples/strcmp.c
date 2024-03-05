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
	char str1[] = "Hello, World";
	char str2[] = "Hello, World!";

	/* string1 is lower than string2 */
	ret = strcmp(str1, str2);
	isEqual(ret);

	/* string1 is lower than string2 */
	ret = strncmp(str1, str2, strlen(str2));
	isEqual(ret);

	/* strings are equal */
	ret = strncmp(str1, str2, strlen(str2) - 1);
	isEqual(ret);

	return 0;
}
