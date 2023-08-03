/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>

#include "utils/utils.h"

#define SEM_FIRST	"/semaphore1"
#define SEM_SECOND	"/semaphore2"

static const char * const messages[] = {
	"I",
	"hate",
	"bullshit"
};

static sem_t *create_or_open_semaphore(const char *semname)
{
	sem_t *sem;

	sem = sem_open(semname, O_CREAT, 0644, 0);
	DIE(sem == NULL, "sem_open");

	return sem;
}

static void delete_semaphore(sem_t *sem, const char *semname)
{
	sem_close(sem);
	sem_unlink(semname);
}

int main(void)
{
	sem_t *sem_first, *sem_second;

	sem_first = create_or_open_semaphore(SEM_FIRST);
	sem_second = create_or_open_semaphore(SEM_SECOND);

	printf("%s\n", messages[0]);
	sem_post(sem_first);
	sem_wait(sem_second);
	printf("%s\n", messages[2]);

	delete_semaphore(sem_first, SEM_FIRST);
	delete_semaphore(sem_second, SEM_SECOND);

	return 0;
}
