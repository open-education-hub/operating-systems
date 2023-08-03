// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>

#include "utils/utils.h"

#define FILE_NAME	"file.txt"
#define MAX_FILE_SIZE	1024

static void read_file(const char *file_name)
{
	int rc;
	FILE *f;
	char buf[MAX_FILE_SIZE] = { 0 };

	/* `f` is a handler to the file. */
	f = fopen(file_name, "r");
	DIE(!f, "fopen");

	rc = fread(buf, 1, sizeof(buf), f);
	DIE(rc < 0, "fread");

	printf("File contents are: %s\n", buf);

	rc = fclose(f);
	DIE(rc < 0, "fclose");
}

static void write_file(const char *file_name)
{
	int rc;
	FILE *f;
	char *msg = "C was here!";

	/* `f` is a handler to the file. */
	f = fopen(file_name, "w");
	DIE(!f, "fopen");

	rc = fwrite(msg, 1, strlen(msg), f);
	DIE(rc < 0, "fwrite");

	puts("Wrote new data to file");

	rc = fclose(f);
	DIE(rc < 0, "fclose");
}

int main(void)
{
	read_file(FILE_NAME);
	write_file(FILE_NAME);
	read_file(FILE_NAME);

	return 0;
}
