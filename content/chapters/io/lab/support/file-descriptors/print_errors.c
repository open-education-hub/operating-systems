// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "utils/utils.h"

void redirect_stderr(void)
{
	/* TODO: Make stderr point to /dev/null using open() and close() */
}

int main(void)
{
	redirect_stderr();

	fprintf(stderr, "This should not be printed\n");

	return 0;
}
