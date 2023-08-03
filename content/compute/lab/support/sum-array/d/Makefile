DC = dmd
DFLAGS = -unittest
GEN_ARRAY = generate_random_array.d
REDUCE = sum_array_threads_reduce

all: $(REDUCE)

$(REDUCE): $(REDUCE).d $(GEN_ARRAY)
	$(DC) $(DFLAGS) $^ -of=$@

clean:
	-rm -f *.o $(REDUCE)
