/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef GRADED_TEST_H_
#define GRADED_TEST_H_	1

/* test function prototype */
typedef int (*test_f)(void);

struct graded_test {
	test_f function;		/* test/evaluation function */
	char *description;		/* test description */
	size_t points;			/* points for each test */
};

void run_test(struct graded_test *test);
void run_tests(struct graded_test *tests, size_t count);

#endif /* GRADED_TEST_H_ */
