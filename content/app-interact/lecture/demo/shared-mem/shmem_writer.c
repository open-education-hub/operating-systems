/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>

#include "utils/utils.h"

#ifdef SHMEM_FILE
#define FILENAME		"shmem.dat"
#elif defined SHMEM_SHM
#define FILENAME		"/shmem.dat"
#else
#error "Unknown shared memory method"
#endif
#define SEM_WRITER_WRITE_1	"/semaphore1"
#define SEM_WRITER_WRITE_2	"/semaphore2"
#define SEM_READER_READ_1	"/semaphore3"
#define SEM_READER_READ_2	"/semaphore4"

#define NUM_PAGES	1
#define MAP_SIZE	(NUM_PAGES * sysconf(_SC_PAGE_SIZE))

#define VALUE_1		100
#define VALUE_2		200

struct map {
	int fd;
	void *ptr;
};

static struct map *create_shared_file_mapping(const char *filename)
{
	struct map *map;
	int rc;

	map = malloc(sizeof(*map));
	DIE(map == NULL, "malloc");

#ifdef SHMEM_FILE
	map->fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
#elif defined SHMEM_SHM
	map->fd = shm_open(filename, O_CREAT | O_RDWR, 0644);
#else
#error "Unknown shared memory method"
#endif
	DIE(map->fd < 0, "open");

	rc = ftruncate(map->fd, MAP_SIZE);
	DIE(rc < 0, "ftruncate");

	map->ptr = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, map->fd, 0);
	DIE(map->ptr == MAP_FAILED, "mmap");

	return map;
}

static void delete_shared_file_mapping(struct map *map, const char *filename)
{
	munmap(map->ptr, MAP_SIZE);
	close(map->fd);
	free(map);
#ifdef SHMEM_FILE
	unlink(filename);
#elif defined SHMEM_SHM
	shm_unlink(filename);
#else
#error "Unknown shared memory method"
#endif
}

static sem_t *create_semaphore(const char *semname)
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
	struct map *map;
	sem_t *sem_writer_write_1;
	sem_t *sem_writer_write_2;
	sem_t *sem_reader_read_1;
	sem_t *sem_reader_read_2;

	map = create_shared_file_mapping(FILENAME);
	sem_writer_write_1 = create_semaphore(SEM_WRITER_WRITE_1);
	sem_writer_write_2 = create_semaphore(SEM_WRITER_WRITE_2);
	sem_reader_read_1 = create_semaphore(SEM_READER_READ_1);
	sem_reader_read_2 = create_semaphore(SEM_READER_READ_2);

	* (int *) (map->ptr) = VALUE_1;
	sem_post(sem_writer_write_1);

	sem_wait(sem_reader_read_1);
	* (int *) (map->ptr) = VALUE_2;
	sem_post(sem_writer_write_2);

	sem_wait(sem_reader_read_2);
	delete_shared_file_mapping(map, FILENAME);
	delete_semaphore(sem_writer_write_1, SEM_WRITER_WRITE_1);
	delete_semaphore(sem_writer_write_2, SEM_WRITER_WRITE_2);
	delete_semaphore(sem_reader_read_1, SEM_READER_READ_1);
	delete_semaphore(sem_reader_read_2, SEM_READER_READ_2);

	return 0;
}
