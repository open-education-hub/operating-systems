/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>

#include "utils/utils.h"

#define NUM_STEPS	1000000
#define NUM_PROCESSES	2
#define FILENAME	"var.dat"

static sem_t *sem;
static int fd;

static void acquire_lock(void)
{
	int rc = sem_wait(sem);

	DIE(rc, "sem_wait");
}

static void release_lock(void)
{
	int rc = sem_post(sem);

	DIE(rc, "sem_post");
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

	sem = mmap(NULL, sizeof(*sem), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	DIE(sem == MAP_FAILED, "mmap");

	rc = sem_init(sem, 1, 1);
	DIE(rc, "sem_init");

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

	rc = sem_destroy(sem);
	DIE(rc, "sem_destroy");

	munmap(sem, sizeof(*sem));

	return 0;
}
