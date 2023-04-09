GEN_ARRAY = generate_random_array.c
OMP = sum_array_threads_reduce

all: $(BINARIES)

%: %.c $(GEN_ARRAY)
	$(CC) $(CFLAGS) $^ -o $@

$(OMP): $(OMP).c $(GEN_ARRAY)
	$(CC) $(CFLAGS) $^ -o $@ -fopenmp

clean:
	-rm -f *.o $(BINARIES)

.PHONY: all clean
