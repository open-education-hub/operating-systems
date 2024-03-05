// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#include "./graded_test.h"

#define RDONLY_FILE "./file_RDONLY"
#define NON_EXISTENT_FILE "./file_NONEXISTENT"
#define RW_FILE "./file_RW"
#define CREATE_FILE "./file_CREATE"
#define DIR_FILE "./dir"
#define EMPTY_FILE "./file_EMPTY"

static int test_open_non_existent_file(void)
{
	int fd;

	fd = open(NON_EXISTENT_FILE, O_RDONLY);

	return fd == -1 && errno == ENOENT;
}

static int test_open_file_as_directory(void)
{
	int fd;

	fd = open(RDONLY_FILE, O_DIRECTORY | O_RDONLY);

	return fd == -1 && errno == ENOTDIR;
}

static int test_open_directory_for_writing(void)
{
	int fd;


	fd = open(DIR_FILE, O_WRONLY);
	return fd == -1 && errno == EISDIR;
}

static int test_open_force_invalid_creation(void)
{
	int fd;

	fd = open(RDONLY_FILE, O_CREAT | O_EXCL);

	return fd == -1 && errno == EEXIST;
}

static int test_open_close_existent_file(void)
{
	int fd;

	fd = open(RDONLY_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	fd = close(fd);
	if (fd < 0)
		return 0;

	return 1;
}

static int test_open_close_create_file(void)
{
	int fd;

	fd = open(CREATE_FILE, O_CREAT | O_RDWR, S_IRUSR);
	if (fd < 0)
		return 0;

	fd = close(fd);
	if (fd < 0)
		return 0;

	return 1;
}

static int test_open_read_write_only_mode(void)
{
	int fd;
	char buff[10];
	ssize_t len;

	fd = open(RW_FILE, O_WRONLY);
	if (fd < 0)
		return 0;

	len = read(fd, buff, 10);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return len < 0;
}

static int test_open_write_read_only_mode(void)
{
	int fd;
	ssize_t len;

	fd = open(RW_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	len = write(fd, "aaa", 3);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return len < 0;
}

static int test_lseek_invalid_fd(void)
{
	int r;

	r = lseek(-1, 0, 0);

	return r == -1 && errno == EBADF;
}

static int test_lseek_invalid_whence(void)
{
	int r, fd;

	fd = open(RDONLY_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	r = lseek(fd, 0, -1);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == -1 && errno == EINVAL;
}

static int test_lseek_invalid_offset(void)
{
	int r, fd;

	fd = open(RDONLY_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	r = lseek(fd, -1, SEEK_SET);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == -1 && errno == EINVAL;
}

static int test_lseek_set(void)
{
	int r, fd;

	fd = open(RDONLY_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	r = lseek(fd, 100, SEEK_SET);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == 100;
}

static int test_lseek_cur(void)
{
	int r, fd;

	fd = open(RDONLY_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	r = lseek(fd, 100, SEEK_CUR);
	r = lseek(fd, 100, SEEK_CUR);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == 200;
}

static int test_lseek_end(void)
{
	int r, fd;

	fd = open(EMPTY_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	r = lseek(fd, 300, SEEK_END);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == 300;
}

static int test_lseek_combined(void)
{
	int r, fd;

	fd = open(EMPTY_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	r = lseek(fd, 100, SEEK_SET);
	r = lseek(fd, 300, SEEK_CUR);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == 400;
}

static int test_truncate_invalid_size(void)
{
	int r;

	r = truncate(RW_FILE, -1);

	return r == -1 && errno == EINVAL;
}

static int test_truncate_directory(void)
{
	int r;

	r = truncate(DIR_FILE, 10);

	return r == -1 && errno == EISDIR;
}

static int test_truncate_non_existent_file(void)
{
	int r;

	r = truncate(NON_EXISTENT_FILE, 10);

	return r == -1 && errno == ENOENT;
}

static int test_truncate_file(void)
{
	int r;

	r = truncate(RW_FILE, 10);

	return r == 0;
}

static int test_ftruncate_read_only_file(void)
{
	int r, fd;

	fd = open(RDONLY_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	r = ftruncate(fd, 10);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == -1 && (errno == EINVAL || errno == EBADF);
}

static int test_ftruncate_invalid_size(void)
{
	int r, fd;

	fd = open(RW_FILE, O_WRONLY);
	if (fd < 0)
		return 0;

	r = ftruncate(fd, -1);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == -1 && errno == EINVAL;
}

static int test_ftruncate_directory(void)
{
	int r, fd;

	fd = open(DIR_FILE, O_RDONLY);
	if (fd < 0)
		return 0;

	r = ftruncate(fd, 10);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == -1 && errno == EINVAL;
}

static int test_ftruncate_bad_fd(void)
{
	int r;

	r = ftruncate(-1, 10);

	return r == -1 && errno == EBADF;
}

static int test_ftruncate_file(void)
{
	int r, fd;

	fd = open(RW_FILE, O_WRONLY);
	if (fd < 0)
		return 0;

	r = ftruncate(fd, 10);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == 0;
}

static int test_stat_non_existent_file(void)
{
	int r;
	struct stat s;

	r = stat(NON_EXISTENT_FILE, &s);

	return r == -1 && errno == ENOENT;
}

static int test_stat_regular_file(void)
{
	int r;
	struct stat s;

	r = stat(RW_FILE, &s);

	return r == 0;
}

static int test_fstat_bad_fd(void)
{
	int r;
	struct stat s;

	r = fstat(-1, &s);

	return r == -1 && errno == EBADF;
}

static int test_fstat_regular_file(void)
{
	int r, fd;
	struct stat s;

	fd = open(RW_FILE, O_RDWR);
	if (fd < 0)
		return 0;

	r = fstat(fd, &s);

	fd = close(fd);
	if (fd < 0)
		return 0;

	return r == 0;
}

static struct graded_test io_tests[] = {
	{ test_open_non_existent_file, "test_open_non_existent_file", 9 },
	{ test_open_file_as_directory, "test_open_file_as_directory", 9 },
	{ test_open_directory_for_writing, "test_open_directory_for_writing", 9 },
	{ test_open_force_invalid_creation, "test_open_force_invalid_creation", 9},
	{ test_open_close_existent_file, "test_open_close_existent_file", 9},
	{ test_open_close_create_file, "test_open_close_create_file", 9},
	{ test_open_read_write_only_mode, "test_open_read_write_only_mode", 9 },
	{ test_open_write_read_only_mode, "test_open_write_read_only_mode", 9 },
	{ test_lseek_invalid_fd, "test_lseek_invalid_fd", 9 },
	{ test_lseek_invalid_whence, "test_lseek_invalid_whence", 9 },
	{ test_lseek_invalid_offset, "test_lseek_invalid_offset", 9 },
	{ test_lseek_set, "test_lseek_set", 9 },
	{ test_lseek_cur, "test_lseek_cur", 9 },
	{ test_lseek_end, "test_lseek_end", 9 },
	{ test_lseek_combined, "test_lseek_combined", 9 },
	{ test_truncate_invalid_size, "test_truncate_invalid_size", 9 },
	{ test_truncate_directory, "test_truncate_directory", 8 },
	{ test_truncate_non_existent_file, "test_truncate_non_existent_file", 8 },
	{ test_truncate_file, "test_truncate_file", 8 },
	{ test_ftruncate_read_only_file, "test_ftruncate_read_only_file", 8 },
	{ test_ftruncate_invalid_size, "test_ftruncate_invalid_size", 8 },
	{ test_ftruncate_directory, "test_ftruncate_directory", 8 },
	{ test_ftruncate_bad_fd, "test_ftruncate_bad_fd", 8 },
	{ test_ftruncate_file, "test_ftruncate_file", 8 },
	{ test_stat_non_existent_file, "test_stat_non_existent_file", 8 },
	{ test_stat_regular_file, "test_stat_regular_file", 8 },
	{ test_fstat_bad_fd, "test_fstat_bad_fd", 8 },
	{ test_fstat_regular_file, "test_fstat_regular_file", 8 },
};

int main(void)
{
	run_tests(io_tests, sizeof(io_tests) / sizeof(io_tests[0]));

	return 0;
}
