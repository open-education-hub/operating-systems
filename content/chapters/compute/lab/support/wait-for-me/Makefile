DC = dmd
BINARY = wait_for_me_threads

all: $(BINARY)

%: %.d
	$(DC) $(DFLAGS) $^ -of=$@

clean:
	-rm -f *.o $(BINARIES)

.PHONY: all clean
