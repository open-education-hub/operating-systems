BINARIES = sum_array_sequential sum_array_threads sum_array_processes sum_array_threads_openmp
CFLAGS += -fopenmp
LDFLAGS += -fopenmp
include ../../../../../../common/makefile/multiple.mk

sum_array_sequential: sum_array_sequential.o generate_random_array.o

sum_array_threads: sum_array_threads.o generate_random_array.o

sum_array_processes: sum_array_processes.o generate_random_array.o

sum_array_threads_openmp: sum_array_threads_openmp.o generate_random_array.o
