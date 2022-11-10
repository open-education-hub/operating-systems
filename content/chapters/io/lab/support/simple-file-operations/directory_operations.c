// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>

#include "utils/utils.h"

#define DIR_NAME	"dir"

static void open_directory(const char *dir_name)
{
	FILE *f;

	f = fopen(dir_name, "w");
	DIE(!f, "fopen");
}

int main(void)
{
	open_directory(DIR_NAME);
	return 0;
}
