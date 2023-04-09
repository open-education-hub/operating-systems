#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <omp.h>

#include "generate_random_array.h"

#define ARR_LEN 100000000

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
		exit(1);
	}

	int *array = malloc(sizeof(*array) * ARR_LEN);
	if (!array)
	{
		fprintf(stderr, "Error when allocating array: %s\n", strerror(errno));
		exit(1);
	}

	generateRandomArray(ARR_LEN, array);

	int numThreads = atoi(argv[1]);

	omp_set_num_threads(numThreads);

	struct timeval start, stop;
	long time, result;
	int ret;

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
