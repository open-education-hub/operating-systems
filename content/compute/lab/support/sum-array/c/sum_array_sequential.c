// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

#include "include/generate_random_array.h"
#include "include/array_utils.h"
#include "utils/utils.h"

int main(void)
{
	long result = 0;
	struct timeval start, stop;
	long time;
	int *array;

	array = malloc(sizeof(*array) * ARR_LEN);
	DIE(!array, "Error when allocating array");

	generate_random_array(ARR_LEN, array);

	gettimeofday(&start, NULL);

	for (int i = 0; i < ARR_LEN; i++)
		result += array[i];

	gettimeofday(&stop, NULL);

	time = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;

	printf("Array sum is %ld\nTime spent: %lu miliseconds\n", result, time);

	free(array);

	return 0;
}
