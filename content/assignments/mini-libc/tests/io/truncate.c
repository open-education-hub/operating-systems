// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define EXISTENT_FILE	"./existent_file"
#define FILE_SIZE	20

/* Truncate file, check that call succeeds. */
int main(void)
{
	int r;

	r = truncate(EXISTENT_FILE, FILE_SIZE);
	if (r < 0)
		exit(EXIT_FAILURE);

	return 0;
}
