// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "page_mapper.h"

int main(void)
{
	do_map(256);
	do_map(10);

	return 0;
}
