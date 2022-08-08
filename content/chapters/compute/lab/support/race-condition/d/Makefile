DC = dmd
BINARIES = race_condition race_condition_mutex race_condition_atomic

all: $(BINARIES)

%: %.d
	$(DC) $(DFLAGS) $^ -of=$@

clean:
	-rm -f *.o $(BINARIES)

.PHONY: all clean
