// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "include/generate_random_array.h"
#include "include/array_utils.h"
#include "utils/utils.h"

static void calculate_array_part_sum(int *array, size_t start, size_t end,
				     long *results, size_t tid)
{
	long sum_array = 0;
	int *seg_fault_ptr = NULL;

	for (size_t i = start; i < end; ++i)
		sum_array += array[i];

	if (tid == 2)
		*seg_fault_ptr = 42;

	results[tid] = sum_array;
}

static inline void *create_shared_results_array(size_t num_processes)
{
	/*
	 * This buffer will be shared by the process that creates it and all its
	 * children due to the `MAP_SHARED` argument
	 */
	return mmap(NULL, num_processes * sizeof(long),
		    PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
}

int main(int argc, char *argv[])
{
	int num_processes, ret = 0;
	struct timeval start, stop;
	long time;
	pid_t *children;
	pid_t pidret;
	long *results;
	long final_result = 0;
	int *array;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
		exit(1);
	}

	num_processes = atoi(argv[1]);

	results = (long *)create_shared_results_array(num_processes);
	DIE(!results, "Error when mapping results array");

	children = malloc(sizeof(*children) * num_processes);
	if (!children) {
		ret = errno;
		fprintf(stderr, "Error when allocating children\n");
		goto error_malloc_children;
	}

	array = malloc(sizeof(*array) * ARR_LEN);
	if (!array) {
		ret = errno;
		fprintf(stderr, "Error when allocating array\n");
		goto error_malloc_array;
	}

	generate_random_array(ARR_LEN, array);

	gettimeofday(&start, NULL);

	for (int i = 0; i < num_processes; ++i) {
		size_t elems_per_process = ARR_LEN / num_processes;
		size_t start = i * elems_per_process;
		size_t end = min((size_t)ARR_LEN, (i + 1) * elems_per_process);

		// Spawn another process with the current one as its parent.
		children[i] = fork();
		switch (children[i]) {
		case -1:
			ret = 1;
			goto end;
		case 0:
			calculate_array_part_sum(array, start, end, results, i);
			goto end;
		default:
			continue;
		}
	}

	for (int i = 0; i < num_processes; ++i) {
		pidret = waitpid(children[i], NULL, 0);
		if (pidret < 0) {
			fprintf(stderr, "waitpid returned error\n");
			continue;
		}
		final_result += results[i];
	}

	gettimeofday(&stop, NULL);

	time = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;

	printf("Array sum is %ld\nTime spent: %lu ms\n", final_result, time);

end:
	free(array);

error_malloc_array:
	free(children);

error_malloc_children:
	munmap(results, num_processes * sizeof(*results));

	return ret;
}
