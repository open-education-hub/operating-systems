#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "generate_random_array.h"

#define ARR_LEN 100000000

#define min(a, b)               \
	({                          \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		_a < _b ? _a : _b;      \
	})

static void calculateArrayPartSum(int *array, size_t start, size_t end,
								  long *results, size_t tid)
{
	long sumArray = 0;

	for (size_t i = start; i < end; ++i)
		sumArray += array[i];

	results[tid] = sumArray;
}

static inline void *createSharedResultsArray(size_t numProcesses)
{
	// This buffer will be shared by the process that creates it and all its
	// children due to the `MAP_SHARED` argument
	return mmap(NULL, numProcesses * sizeof(long),
				PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
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

	int numProcesses = atoi(argv[1]);

	struct timeval start, stop;
	long time;
	pid_t children[numProcesses];
	int ret;
	long *results = (long *)createSharedResultsArray(numProcesses);

	gettimeofday(&start, NULL);

	for (int i = 0; i < numProcesses; ++i)
	{
		size_t elemsPerProcess = ARR_LEN / numProcesses;
		size_t start = i * elemsPerProcess;
		size_t end = min(ARR_LEN, (i + 1) * elemsPerProcess);

		// Spawn another process with the current one as its parent.
		children[i] = fork();
		switch (children[i])
		{
		case -1:
			exit(1);
		case 0:
			calculateArrayPartSum(array, start, end, results, i);
			exit(0);
		default:
			continue;
		}
	}

	long finalResult = 0;

	for (int i = 0; i < numProcesses; ++i)
	{
		waitpid(children[i], NULL, 0);
		finalResult += results[i];
	}

	gettimeofday(&stop, NULL);

	time = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;

	printf("Array sum is %ld\nTime spent: %lu ms\n", finalResult, time);

	free(array);

	return 0;
}
