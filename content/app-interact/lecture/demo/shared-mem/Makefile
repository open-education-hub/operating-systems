BINARIES = shmem_threads shmem_file_reader shmem_file_writer shmem_shm_reader shmem_shm_writer
LDLIBS ?= -lpthread -lrt

include ../../../../../common/makefile/multiple.mk

shmem_file_reader.o: shmem_reader.c ../../../../../common/utils/log/log.h ../../../../../common/utils/utils.h
	$(CC) $(CPPFLAGS) -DSHMEM_FILE $(CFLAGS) -c -o $@ $<

shmem_file_writer.o: shmem_writer.c ../../../../../common/utils/log/log.h ../../../../../common/utils/utils.h
	$(CC) $(CPPFLAGS) -DSHMEM_FILE $(CFLAGS) -c -o $@ $<

shmem_shm_reader.o: shmem_reader.c ../../../../../common/utils/log/log.h ../../../../../common/utils/utils.h
	$(CC) $(CPPFLAGS) -DSHMEM_SHM $(CFLAGS) -c -o $@ $<

shmem_shm_writer.o: shmem_writer.c ../../../../../common/utils/log/log.h ../../../../../common/utils/utils.h
	$(CC) $(CPPFLAGS) -DSHMEM_SHM $(CFLAGS) -c -o $@ $<

clean::
	-rm -f shmem_file_writer.o shmem_file_reader.o
	-rm -f shmem_shm_writer.o shmem_shm_reader.o
