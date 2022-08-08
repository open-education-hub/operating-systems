DC = dmd
BINARY = sum_array_processes

all: $(BINARY)

$(BINARY): $(wildcard *.d)
	$(DC) $(DFLAGS) $^ -of=$@

clean:
	-rm -f *.o $(BINARY)

.PHONY: all clean
