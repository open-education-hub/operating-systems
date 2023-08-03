// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

#include "./graded_test.h"

static int test_strcpy(void)
{
	char src[] = "sticksandstones";
	char dst[128];
	size_t len;

	/*
	 * Add 'Z' on future correct location of the NUL-terminator.
	 * This way, in case of a faulty implementation that fails to
	 * add the NUL-terminator, the test will fail.
	 */
	dst[sizeof(src)-1] = 'Z';
	strcpy(dst, src);
	len = strlen(dst);

	return len == (sizeof(src)-1);
}

static int test_strcpy_append(void)
{
	char src[] = "sticksandstones";
	char dst[128];
	size_t len;

	dst[2*sizeof(src) - 2] = 'Z';
	strcpy(dst, src);
	strcpy(dst + sizeof(src)-1, src);
	len = strlen(dst);

	return len == 2*sizeof(src) - 2;
}

static int test_strncpy(void)
{
	char src[] = "sticksandstones";
	char dst[128];
	size_t len;

	dst[sizeof(src)-1] = 'Z';
	strncpy(dst, src, 128);
	len = strlen(dst);

	return len == sizeof(src) - 1;
}

static int test_strncpy_cut(void)
{
	char src[] = "sticksandstones";
	char dst[128];
	size_t len;

	dst[11] = '\0';
	dst[10] = 'Z';
	strncpy(dst, src, 10);
	len = strlen(dst);

	return len == 11;
}

static int test_strcat(void)
{
	char part1[] = "sticksandstones";
	char part2[] = "willbreakyourbones";
	char dst[128];
	size_t len;

	dst[sizeof(part1) + sizeof(part2) - 2] = 'Z';
	strcpy(dst, part1);
	strcat(dst, part2);
	len = strlen(dst);

	return len == sizeof(part1) + sizeof(part2) - 2;
}

static int test_strcat_from_zero(void)
{
	char part1[] = "sticksandstones";
	char dst[128];
	size_t len;

	dst[0] = '\0';
	strcat(dst, part1);
	len = strlen(dst);

	return len == sizeof(part1) - 1;
}

static int test_strcat_multiple(void)
{
	char part1[] = "sticksandstones";
	char part2[] = "willbreakyourbones";
	char part3[] = "andthensomemore";
	char dst[128];
	size_t len;

	dst[sizeof(part1) + sizeof(part2) + sizeof(part3) - 3] = 'Z';
	strcpy(dst, part1);
	strcat(dst, part2);
	strcat(dst, part3);
	len = strlen(dst);

	return len == sizeof(part1) + sizeof(part2) + sizeof(part3) - 3;
}

static int test_strncat(void)
{
	char part1[] = "sticksandstones";
	char part2[] = "willbreakyourbones";
	char dst[128];
	size_t len;

	dst[sizeof(part1) + sizeof(part2) - 2] = 'Z';
	strcpy(dst, part1);
	strncat(dst, part2, 128 - sizeof(part1));
	len = strlen(dst);

	return len == sizeof(part1) + sizeof(part2) - 2;
}

static int test_strncat_cut(void)
{
	char part1[] = "sticksandstones";
	char part2[] = "willbreakyourbones";
	char dst[128];
	size_t len;

	strcpy(dst, part1);
	dst[sizeof(part1) + 9] = '\0';
	dst[sizeof(part1) + 8] = 'Z';
	strncat(dst, part2, 8);
	len = strlen(dst);

	return len == sizeof(part1) + 7;
}

static int test_strcmp_equal(void)
{
	char s1[] = "sticksandstones";
	char s2[] = "sticksandstones";
	int res;

	res = strcmp(s1, s2);

	return res == 0;
}

static int test_strcmp_same_size_less(void)
{
	char s1[] = "sticksandstonea";
	char s2[] = "sticksandstones";
	int res;

	res = strcmp(s1, s2);

	return res < 0;
}

static int test_strcmp_same_size_greater(void)
{
	char s1[] = "sticksandstones";
	char s2[] = "sticksandstonea";
	int res;

	res = strcmp(s1, s2);

	return res > 0;
}

static int test_strcmp_diff_size_less(void)
{
	char s1[] = "sticksandstones";
	char s2[] = "sticksandstonest";
	int res;

	res = strcmp(s1, s2);

	return res < 0;
}

static int test_strcmp_diff_size_greater(void)
{
	char s1[] = "sticksandstonest";
	char s2[] = "sticksandstones";
	int res;

	res = strcmp(s1, s2);

	return res > 0;
}

static int test_strncmp_equal_size_equal(void)
{
	char s1[] = "sticksandstones";
	char s2[] = "sticksandstones";
	int res;

	res = strncmp(s1, s2, sizeof(s1) - 1);

	return res == 0;
}

static int test_strncmp_diff_contents_equal(void)
{
	char s1[] = "sticksandstonea";
	char s2[] = "sticksandstones";
	int res;

	res = strncmp(s1, s2, sizeof(s1) - 2);

	return res == 0;
}

static int test_strncmp_diff_size_equal(void)
{
	char s1[] = "sticksand";
	char s2[] = "sticksandstones";
	int res;

	res = strncmp(s1, s2, sizeof(s1) - 1);

	return res == 0;
}

static int test_strchr_exists(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strchr(s, 'a');

	return p == s + 6;
}

static int test_strchr_exists_twice(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strchr(s, 'n');

	return p == s + 7;
}

static int test_strchr_not_exists(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strchr(s, 'Z');

	return p == NULL;
}

static int test_strrchr_exists(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strrchr(s, 'a');

	return p == s + 6;
}

static int test_strrchr_exists_twice(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strrchr(s, 'n');

	return p == s + 12;
}

static int test_strrchr_not_exists(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strrchr(s, 'Z');

	return p == NULL;
}

static int test_strstr_exists(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strstr(s, "andst");

	return p == s + 6;
}

static int test_strstr_exists_twice(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strstr(s, "st");

	return p == s;
}

static int test_strstr_not_exists(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strstr(s, "andsta");

	return p == NULL;
}

static int test_strrstr_exists(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strrstr(s, "andst");

	return p == s + 6;
}

static int test_strrstr_exists_twice(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strrstr(s, "st");

	return p == s + 9;
}

static int test_strrstr_not_exists(void)
{
	char s[] = "sticksandstones";
	char *p;

	p = strrstr(s, "andsta");

	return p == NULL;
}

static int test_memcpy(void)
{
	char src[] = "sticksandstones";
	char dst[128];
	size_t len;

	memcpy(dst, src, sizeof(src));
	len = strlen(dst);

	return len == (sizeof(src)-1);
}

static int test_memcpy_part(void)
{
	char src[] = "sticksandstones";
	char dst[128];
	size_t len;

	dst[11] = '\0';
	dst[10] = 'Z';
	memcpy(dst, src, 10);
	len = strlen(dst);

	return len == 11;
}

static int test_memcmp_equal_size_equal(void)
{
	char s1[] = "sticksandstones";
	char s2[] = "sticksandstones";
	int res;

	res = memcmp(s1, s2, sizeof(s1) - 1);

	return res == 0;
}

static int test_memcmp_diff_contents_equal(void)
{
	char s1[] = "sticksandstonea";
	char s2[] = "sticksandstones";
	int res;

	res = memcmp(s1, s2, sizeof(s1) - 2);

	return res == 0;
}

static int test_memcmp_diff_size_equal(void)
{
	char s1[] = "sticksand";
	char s2[] = "sticksandstones";
	int res;

	res = memcmp(s1, s2, sizeof(s1) - 1);

	return res == 0;
}

static int test_memset(void)
{
	char s1[] = "aaaaaaaa";
	char s2[8];
	int res;

	memset(s2, 'a', 8);
	res = memcmp(s1, s2, 8);

	return res == 0;
}

static int test_memset_part(void)
{
	char s1[] = "aaaa";
	char s2[8];
	int res;

	memset(s2, 'b', 8);
	memset(s2 + 4, 'a', 8);
	res = memcmp(s1, s2 + 4, 4);

	return res == 0;
}

static int test_memmove_apart(void)
{
	char src[] = "sticksandstones";
	char dst[128];
	size_t len;

	memmove(dst, src, sizeof(src));
	len = strlen(dst);

	return len == (sizeof(src)-1);
}

static int test_memmove_src_before_dst(void)
{
	char src[128];
	char *dst = src + 16;

	memset(src, 'a', 128);
	memset(dst, 'b', 112);
	memmove(dst, src, 112);

	return dst[0] == 'a' && dst[1] == 'a';
}

static int test_memmove_src_after_dst(void)
{
	char dst[128];
	char *src = dst + 16;

	memset(dst, 'b', 128);
	memset(src, 'a', 112);
	memmove(dst, src, 112);

	return dst[0] == 'a' && dst[1] == 'a';
}

static struct graded_test string_tests[] = {
	{ test_strcpy, "test_strcpy", 9 },
	{ test_strcpy_append, "test_strcpy_append", 9 },
	{ test_strncpy, "test_strncpy", 9 },
	{ test_strncpy_cut, "test_strncpy_cut", 9 },
	{ test_strcat, "test_strcat", 9},
	{ test_strcat_from_zero, "test_strcat_from_zero", 9},
	{ test_strcat_multiple, "test_strcat_multiple", 9},
	{ test_strncat, "test_strncat", 9 },
	{ test_strncat_cut, "test_strncat_cut", 9 },
	{ test_strcmp_equal, "test_strcmp_equal", 9 },
	{ test_strcmp_same_size_less, "test_strcmp_same_size_less", 1 },
	{ test_strcmp_same_size_greater, "test_strcmp_same_size_greater", 9 },
	{ test_strcmp_diff_size_less, "test_strcmp_diff_size_less", 1 },
	{ test_strcmp_diff_size_greater, "test_strcmp_diff_size_greater", 9 },
	{ test_strncmp_equal_size_equal, "test_strncmp_equal_size_equal", 9 },
	{ test_strncmp_diff_contents_equal, "test_strncmp_diff_contents_equal", 9 },
	{ test_strncmp_diff_size_equal, "test_strncmp_diff_size_equal", 9 },
	{ test_strchr_exists, "test_strchr_exists", 11 },
	{ test_strchr_exists_twice, "test_strchr_exists_twice", 9 },
	{ test_strchr_not_exists, "test_strchr_not_exists", 1 },
	{ test_strrchr_exists, "test_strrchr_exists", 11 },
	{ test_strrchr_exists_twice, "test_strrchr_exists_twice", 9 },
	{ test_strrchr_not_exists, "test_strrchr_not_exists", 1 },
	{ test_strstr_exists, "test_strstr_exists", 11 },
	{ test_strstr_exists_twice, "test_strstr_exists_twice", 9 },
	{ test_strstr_not_exists, "test_strstr_not_exists", 1 },
	{ test_strrstr_exists, "test_strrstr_exists", 11 },
	{ test_strrstr_exists_twice, "test_strrstr_exists_twice", 9 },
	{ test_strrstr_not_exists, "test_strrstr_not_exists", 1 },
	{ test_memcpy, "test_memcpy", 11 },
	{ test_memcpy_part, "test_memcpy_part", 9 },
	{ test_memcmp_equal_size_equal, "test_memcmp_equal_size_equal", 9 },
	{ test_memcmp_diff_contents_equal, "test_memcmp_diff_contents_equal", 9 },
	{ test_memcmp_diff_size_equal, "test_memcmp_diff_size_equal", 9 },
	{ test_memset, "test_memset", 9 },
	{ test_memset_part, "test_memset_part", 9 },
	{ test_memmove_apart, "test_memmove_apart", 9 },
	{ test_memmove_src_before_dst, "test_memmove_src_before_dst", 9 },
	{ test_memmove_src_after_dst, "test_memmove_src_after_dst", 9 },
};

int main(void)
{
	run_tests(string_tests, sizeof(string_tests) / sizeof(string_tests[0]));

	return 0;
}
