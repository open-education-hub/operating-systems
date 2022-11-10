/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <unistd.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

int main(void)
{
	int rc;
	char buffer[BUFSIZ];

	rc = read(0, buffer, BUFSIZ);
	DIE(rc < 0, "read");

	printf("Message is: %s\n", buffer);
	return 0;
}
