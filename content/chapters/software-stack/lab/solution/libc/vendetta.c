/* SPDX-License-Identifier: BSD-3-Clause */

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	int fd;
	FILE *f;

	fd = open("a.txt", O_RDWR | O_CREAT, 0644);
	close(fd);

	f = fopen("a.txt", "w");
	fclose(f);

	printf("sin(0): %f, sin(PI/2): %f\n", sin(0), sin(M_PI / 2));

	return 0;
}
