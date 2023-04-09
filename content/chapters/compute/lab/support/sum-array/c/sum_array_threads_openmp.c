// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <omp.h>

#include "include/generate_random_array.h"
#include "include/array_utils.h"
#include "utils/utils.h"

int main(int argc, char *argv[])
{
	struct timeval start, stop;
	long time, result = 0;
	int num_threads;
	int *array;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
		exit(1);
	}

	array = malloc(sizeof(*array) * ARR_LEN);
	DIE(!array, "Error when allocating array");

	generate_random_array(ARR_LEN, array);

	num_threads = atoi(argv[1]);

	omp_set_num_threads(num_threads);

	gettimeofday(&start, NULL);

#pragma omp parallel for reduction(+ \
				   : result)
	for (int i = 0; i < ARR_LEN; i++)
		result += array[i];

	gettimeofday(&stop, NULL);

	time = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;

	printf("Array sum is %ld\nTime spent: %lu ms\n", result, time);

	free(array);

	return 0;
}
