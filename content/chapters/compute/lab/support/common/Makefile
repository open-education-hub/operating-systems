DC = dmd
DFLAGS = -unittest
GEN_ARRAY = generate_random_array.d

all: $(BINARIES)

%: %.d $(GEN_ARRAY)
	$(DC) $(DFLAGS) $^ -of=$@

clean:
	-rm -f *.o $(BINARIES)

.PHONY: all clean
