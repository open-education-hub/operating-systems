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

struct map {
	int fd;
	void *ptr;
};

static struct map *open_shared_file_mapping(const char *filename)
{
	struct map *map;

	map = malloc(sizeof(*map));
	DIE(map == NULL, "malloc");

#ifdef SHMEM_FILE
	map->fd = open(filename, O_RDWR);
#elif defined SHMEM_SHM
	map->fd = shm_open(filename, O_RDWR, 0);
#else
#error "Unknown shared memory method"
#endif
	DIE(map->fd < 0, "open");

	map->ptr = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, map->fd, 0);
	DIE(map->ptr == MAP_FAILED, "mmap");

	return map;
}

static void close_shared_file_mapping(struct map *map)
{
	munmap(map->ptr, MAP_SIZE);
	close(map->fd);
	free(map);
}

static sem_t *open_semaphore(const char *semname)
{
	sem_t *sem;

	sem = sem_open(semname, O_RDWR);
	DIE(sem == NULL, "sem_open");

	return sem;
}

static void close_semaphore(sem_t *sem)
{
	sem_close(sem);
}

int main(void)
{
	struct map *map;
	sem_t *sem_writer_write_1;
	sem_t *sem_writer_write_2;
	sem_t *sem_reader_read_1;
	sem_t *sem_reader_read_2;

	map = open_shared_file_mapping(FILENAME);
	sem_writer_write_1 = open_semaphore(SEM_WRITER_WRITE_1);
	sem_writer_write_2 = open_semaphore(SEM_WRITER_WRITE_2);
	sem_reader_read_1 = open_semaphore(SEM_READER_READ_1);
	sem_reader_read_2 = open_semaphore(SEM_READER_READ_2);

	sem_wait(sem_writer_write_1);
	printf("value is %d\n", * (int *) (map->ptr));
	sem_post(sem_reader_read_1);

	sem_wait(sem_writer_write_2);
	printf("value is %d\n", * (int *) (map->ptr));
	sem_post(sem_reader_read_2);

	close_shared_file_mapping(map);
	close_semaphore(sem_writer_write_1);
	close_semaphore(sem_writer_write_2);
	close_semaphore(sem_reader_read_1);
	close_semaphore(sem_reader_read_2);

	return 0;
}
