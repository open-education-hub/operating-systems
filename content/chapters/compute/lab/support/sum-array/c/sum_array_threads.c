// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include "include/generate_random_array.h"
#include "include/array_utils.h"
#include "utils/utils.h"

struct thread_args {
	int *array;
	size_t start;
	size_t end;
	long *results;
	size_t tid;
};

static void *calculate_array_part_sum(void *varg)
{
	struct thread_args *arg = (struct thread_args *)varg;
	long sum_array = 0;

	for (size_t i = arg->start; i < arg->end; i++)
		sum_array += arg->array[i];

	arg->results[arg->tid] = sum_array;

	return NULL;
}

int main(int argc, char *argv[])
{
	int num_threads;
	struct timeval start, stop;
	long time;
	pthread_t *threads;
	long *results;
	struct thread_args *args;
	int ret;
	long final_result = 0;
	int *array;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
		exit(1);
	}

	num_threads = atoi(argv[1]);

	array = malloc(sizeof(*array) * ARR_LEN);
	DIE(!array, "Error when allocating array");

	threads = malloc(sizeof(*threads) * num_threads);
	if (!threads) {
		fprintf(stderr, "Error when allocating threads: %s", strerror(errno));
		ret = errno;
		goto error_malloc_threads;
	}

	results = malloc(sizeof(*results) * num_threads);
	if (!results) {
		fprintf(stderr, "Error when allocating results: %s", strerror(errno));
		ret = errno;
		goto error_malloc_results;
	}

	args = malloc(sizeof(*args) * num_threads);
	if (!args) {
		fprintf(stderr, "Error when allocating thread args: %s", strerror(errno));
		ret = errno;
		goto error_malloc_args;
	}

	generate_random_array(ARR_LEN, array);

	gettimeofday(&start, NULL);

	for (int i = 0; i < num_threads; i++) {
		size_t elems_per_thread = ARR_LEN / num_threads;
		size_t start = i * elems_per_thread;
		size_t end = min((size_t)ARR_LEN, (i + 1) * elems_per_thread);

		args[i].array = array;
		args[i].start = start;
		args[i].end = end;
		args[i].results = results;
		args[i].tid = i;

		ret = pthread_create(&threads[i], NULL, calculate_array_part_sum, (void *)&args[i]);
		if (ret != 0) {
			fprintf(stderr, "Error when creating thread #%d: %s", i, strerror(errno));
			goto error_pthread_create;
		}
	}

	for (int i = 0; i < num_threads; i++)
		pthread_join(threads[i], NULL);

	for (int i = 0; i < num_threads; i++)
		final_result += results[i];

	gettimeofday(&stop, NULL);

	time = 1000 * (stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec) / 1000;

	printf("Array sum is %ld\nTime spent: %lu ms\n", final_result, time);

error_pthread_create:
	free(args);

error_malloc_args:
	free(results);

error_malloc_results:
	free(threads);

error_malloc_threads:
	free(array);

	return ret;
}
