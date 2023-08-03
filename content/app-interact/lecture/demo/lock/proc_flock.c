/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/file.h>

#include "utils/utils.h"

#define NUM_STEPS	1000000
#define NUM_PROCESSES	2
#define FILENAME	"var.dat"
#define LOCK_FILENAME	"var.lock"

static int fd;
static int lockfd;

static void acquire_lock(void)
{
	int rc = flock(lockfd, LOCK_EX);

	DIE(rc, "flock");
}

static void release_lock(void)
{
	int rc = flock(lockfd, LOCK_UN);

	DIE(rc, "flock");
}

static unsigned long var = 0;

static void read_var(void)
{
	lseek(fd, 0, SEEK_SET);
	read(fd, &var, sizeof(var));
}

static void write_var(void)
{
	lseek(fd, 0, SEEK_SET);
	write(fd, &var, sizeof(var));
}

static void increase_var(void)
{
	size_t i;

	for (i = 0; i < NUM_STEPS; i++) {
		acquire_lock();	/* Begin critical section. */
		read_var();
		var++;
		write_var();
		release_lock();	/* End critical section. */
	}
}

int main(void)
{
	int rc;
	size_t i;
	pid_t pids[NUM_PROCESSES];

	lockfd = open(LOCK_FILENAME, O_CREAT | O_TRUNC | O_RDWR, 0644);
	DIE(lockfd < 0, "open");

	fd = open(FILENAME, O_CREAT | O_TRUNC | O_RDWR, 0644);
	DIE(fd < 0, "open");

	/* Initialize value in file. */
	write_var();

	for (i = 0; i < NUM_PROCESSES; i++) {
		pids[i] = fork();
		switch (pids[i]) {
		case -1:
			DIE(pids[i] < 0, "fork");
			break;
		case 0:
			close(lockfd);
			lockfd = open(LOCK_FILENAME, O_RDWR, 0644);
			DIE(lockfd < 0, "open");
			increase_var();
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	}

	for (i = 0; i < NUM_PROCESSES; i++) {
		rc = waitpid(pids[i], NULL, 0);
		DIE(rc < 0, "waitpid");
	}

	read_var();
	printf("var: %lu\n", var);

	close(fd);
	unlink(FILENAME);

	close(lockfd);
	unlink(LOCK_FILENAME);

	return 0;
}
