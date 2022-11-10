DC = dmd
BINARIES = sum_array_processes sum_array_threads

all: $(BINARIES)

sum_array_processes: sum_array_processes.d generate_random_array.d
	$(DC) $^ -of=$@

sum_array_threads: sum_array_threads.d generate_random_array.d
	$(DC) $^ -of=$@

clean:
	-rm -f *.o $(BINARIES)

.PHONY: all clean
