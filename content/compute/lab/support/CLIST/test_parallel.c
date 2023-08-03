#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#include "clist.h"

#define NUM_ELEMS	100000000
#define INT_SIZE	sizeof(int)

static size_t diff_usec(struct timeval start, struct timeval end)
{ 
	return (1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec -
		start.tv_usec);
}

typedef struct {
	CList *l;
	int *elems;
	size_t n;
} list_args_t;

static void *add_to_list(void *arg)
{
	list_args_t *args = (list_args_t *)arg;
	size_t i;

	for (i = 0; i < args->n; ++i)
		args->l->add(args->l, args->elems + i);

	return NULL;
}

static void *remove_from_list(void *arg)
{
	list_args_t *args = (list_args_t *)arg;
	size_t i;

	for (i = 0; i < args->n; ++i)
		args->l->remove(args->l, args->elems[i]);

	return NULL;
}

static void *replace_even_from_list(void *arg)
{
	list_args_t *args = (list_args_t *)arg;
	size_t i;

	for (i = 0; i < args->n; ++i)
		args->l->replace(args->l, args->elems + i, 2 * i);

	return NULL;
}

static void *replace_odd_from_list(void *arg)
{
	list_args_t *args = (list_args_t *)arg;
	size_t i;

	for (i = 0; i < args->n; ++i)
		args->l->replace(args->l, args->elems + i, 2 * i + 1);

	return NULL;
}

static void *replace_same_from_list(void *arg)
{
	list_args_t *args = (list_args_t *)arg;
	size_t i;

	for (i = 0; i < args->n; ++i)
		args->l->replace(args->l, args->elems + i, 0);

	return NULL;
}

static int init_even_elem(size_t idx)
{
	return idx * 2; 
}

static int init_odd_elem(size_t idx)
{
	return idx * 2 + 1; 
}

static int init_remove_elem(size_t idx)
{
	(void)idx;
	return 0;
}

static void create_args(list_args_t *args, CList *l, int (*init_elem)(size_t))
{
	size_t i;

	args->n = NUM_ELEMS / 2;
	args->l = l;

	args->elems = malloc(args->n * INT_SIZE);
	if (!args->elems) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < args->n; ++i)
		args->elems[i] = init_elem(i);
}

static pthread_t spawn_thread(void *(*func)(void *), list_args_t *args)
{
	pthread_t tid;
	int rc = pthread_create(&tid, NULL, func, args);

	if (rc < 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	return tid;
}

static void test_parallel_add_add(void)
{
	int i;
	pthread_t tid1, tid2;
	list_args_t args1, args2;
	struct timeval start, end;
	CList *l = CList_init(INT_SIZE);

	create_args(&args1, l, init_even_elem);
	create_args(&args2, l, init_odd_elem);

	gettimeofday(&start, NULL);
	tid1 = spawn_thread(add_to_list, &args2);
	tid2 = spawn_thread(add_to_list, &args2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	gettimeofday(&end, NULL);

	assert(l->count(l) == NUM_ELEMS);
	for (i = 0; i < NUM_ELEMS; ++i)
		assert(l->firstMatch(l, &i, INT_SIZE, INT_SIZE, 0));

	printf("Add of %i `int`s on 2 threads takes  -  %zu microseconds\n",
		NUM_ELEMS, diff_usec(start, end));
}

static void test_parallel_add_remove(void)
{
	pthread_t tid1, tid2;
	list_args_t args1, args2;
	struct timeval start, end;
	CList *l = CList_init(INT_SIZE);

	create_args(&args1, l, init_even_elem);
	create_args(&args2, l, init_remove_elem);

	gettimeofday(&start, NULL);
	tid1 = spawn_thread(add_to_list, &args2);
	tid2 = spawn_thread(remove_from_list, &args1);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	gettimeofday(&end, NULL);

	printf("Add and Remove of %i `int`s on 2 threads takes  -  %zu microseconds\n",
		NUM_ELEMS / 2, diff_usec(start, end));
}

static void test_parallel_remove_remove(void)
{
	pthread_t tid1, tid2;
	list_args_t args1, args2;
	struct timeval start, end;
	CList *l = CList_init(INT_SIZE);

	create_args(&args1, l, init_even_elem);
	add_to_list(&args1);
	create_args(&args2, l, init_odd_elem);
	add_to_list(&args2);

	/* Always remove the first element. */
	memset(args1.elems, 0, args1.n * INT_SIZE);
	memset(args2.elems, 0, args2.n * INT_SIZE);

	gettimeofday(&start, NULL);
	tid1 = spawn_thread(remove_from_list, &args1);
	tid2 = spawn_thread(remove_from_list, &args2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	gettimeofday(&end, NULL);

	assert(l->count(l) == 0);

	printf("Remove of %i `int`s on 2 threads takes  -  %zu microseconds\n",
		NUM_ELEMS, diff_usec(start, end));
}

static void test_parallel_replace_replace_different(void)
{
	size_t i;
	int j;
	pthread_t tid1, tid2;
	list_args_t args1, args2;
	struct timeval start, end;
	CList *l = CList_init(INT_SIZE);

	create_args(&args1, l, init_even_elem);
	add_to_list(&args1);
	create_args(&args2, l, init_odd_elem);
	add_to_list(&args2);

	for (i = 0; i < args1.n; ++i) {
		args1.elems[i] = -args1.elems[i];
		args2.elems[i] = -args2.elems[i];
	}

	gettimeofday(&start, NULL);
	tid1 = spawn_thread(replace_even_from_list, &args1);
	tid2 = spawn_thread(replace_odd_from_list, &args2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	gettimeofday(&end, NULL);

	assert(l->count(l) == NUM_ELEMS);
	for (j = 0; j < NUM_ELEMS; ++j)
		assert(*(int *) l->at(l, j) == -j);

	printf("Replacing %i `int`s on 2 threads takes  -  %zu microseconds\n",
		NUM_ELEMS, diff_usec(start, end));
}

static void test_parallel_replace_replace_same(void)
{
	size_t i;
	int first_elem;
	pthread_t tid1, tid2;
	list_args_t args1, args2;
	struct timeval start, end;
	CList *l = CList_init(INT_SIZE);

	create_args(&args1, l, init_even_elem);
	add_to_list(&args1);
	create_args(&args2, l, init_odd_elem);
	add_to_list(&args2);

	for (i = 0; i < args1.n; ++i) {
		args1.elems[i] = -args1.elems[i];
		args2.elems[i] = -args2.elems[i];
	}

	gettimeofday(&start, NULL);
	tid1 = spawn_thread(replace_same_from_list, &args1);
	tid2 = spawn_thread(replace_same_from_list, &args2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	gettimeofday(&end, NULL);

	assert(l->count(l) == NUM_ELEMS);
	first_elem = *(int *) l->at(l, 0);
	assert(first_elem == -NUM_ELEMS || first_elem == -NUM_ELEMS + 1);

	printf("Replacing the first element %i timess on 2 threads takes  -  %zu microseconds\n",
		NUM_ELEMS, diff_usec(start, end));
}

int main(void)
{
	test_parallel_add_add();
	test_parallel_add_remove();
	test_parallel_remove_remove();
	test_parallel_replace_replace_different();
	test_parallel_replace_replace_same();

	return 0;
}
