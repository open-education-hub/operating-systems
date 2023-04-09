#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

#include "generate_random_array.h"

#define ARR_LEN 100000000

int main()
{
	int *array = malloc(sizeof(*array) * ARR_LEN);
	if (!array)
	{
		fprintf(stderr, "Error when allocating array: %s\n", strerror(errno));
		exit(1);
	}

	generateRandomArray(ARR_LEN, array);

	long result = 0;
	struct timeval start, stop;
	long time;

	gettimeofday(&start, NULL);

	for (int i = 0; i < ARR_LEN; i++)
		result += array[i];

	gettimeofday(&stop, NULL);

	time = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;

	printf("Array sum is %ld\nTime spent: %lu miliseconds\n", result, time);

	free(array);

	return 0;
}
