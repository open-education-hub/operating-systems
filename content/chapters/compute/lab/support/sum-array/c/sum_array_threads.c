#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include "generate_random_array.h"

#define ARR_LEN 100000000

#define min(a, b)               \
	({                          \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		_a < _b ? _a : _b;      \
	})

struct threadArgs
{
	int *array;
	size_t start;
	size_t end;
	long *results;
	size_t tid;
};

static void *calculateArrayPartSum(void *varg)
{
	struct threadArgs *arg = (struct threadArgs *)varg;
	long sumArray = 0;

	for (int i = arg->start; i < arg->end; i++)
		sumArray += arg->array[i];

	arg->results[arg->tid] = sumArray;

	return NULL;
}

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

	struct timeval start, stop;
	long time;
	pthread_t threads[numThreads];
	long results[numThreads];
	struct threadArgs args[numThreads];
	int ret;

	gettimeofday(&start, NULL);

	for (int i = 0; i < numThreads; i++)
	{
		size_t elemsPerThread = ARR_LEN / numThreads;
		size_t start = i * elemsPerThread;
		size_t end = min(ARR_LEN, (i + 1) * elemsPerThread);

		args[i].array = array;
		args[i].start = start;
		args[i].end = end;
		args[i].results = results;
		args[i].tid = i;

		ret = pthread_create(&threads[i], NULL, calculateArrayPartSum, (void *)&args[i]);
		if (ret != 0)
		{
			fprintf(stderr, "Error when creating thread %d: %s\n", i, strerror(errno));
			exit(1);
		}
	}

	for (int i = 0; i < numThreads; i++)
		pthread_join(threads[i], NULL);

	long finalResult = 0;

	for (int i = 0; i < numThreads; i++)
		finalResult += results[i];

	gettimeofday(&stop, NULL);

	time = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;

	printf("Array sum is %ld\nTime spent: %lu ms\n", finalResult, time);

	free(array);

	return 0;
}
