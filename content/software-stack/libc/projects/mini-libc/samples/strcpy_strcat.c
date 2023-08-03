// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <string.h>

int main(void)
{
	/* strcpy - dst is set to Hello, World!\n */
	char dst[20];
	char *src = "Hello, World!\n";
	char str1[] = "To be or not to be";
	char str2[40];
	char str3[40];
	char str4[80];
	char str5[20];
	char str6[20];

	strcpy(dst, src);
	write(1, dst, strlen(dst));

	/* strncpy - str2 is set to str1 (To be or not to be) */
	strncpy(str2, str1, sizeof(str2));
	write(1, str2, strlen(str2));
	write(1, "\n", 1);

	/* strncpy - str3 is set to partial copy of str2 (To be) */
	strncpy(str3, str2, 5);
	str3[5] = '\0';
	write(1, str3, strlen(str3));
	write(1, "\n", 1);

	/* strcat - concatenate */
	strcpy(str4, "These ");
	strcat(str4, "strings ");
	strcat(str4, "are ");
	strcat(str4, "concatenated.");
	write(1, str4, strlen(str4));
	write(1, "\n", 1);

	/* strncat - concatenate str5 with partial copy of str6 - (To be or not) */
	strcpy(str5, "To be ");
	strcpy(str6, "or not to be");
	strncat(str5, str6, 6);
	write(1, str5, strlen(str5));
	write(1, "\n", 1);

	return 0;
}
