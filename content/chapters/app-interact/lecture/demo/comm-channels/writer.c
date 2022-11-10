/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <unistd.h>

#include "utils/utils.h"

static const char message[] = "Hello, world!";

int main(void)
{
	int rc;

	rc = write(1, message, sizeof(message));
	DIE(rc < 0, "write");

	return 0;
}
