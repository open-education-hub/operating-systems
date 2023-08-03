DC = gdc

.PHONY: all clean

all: operators refcount_skel

operators: operators.d
	$(DC) -o $@ $^

refcount_skel: refcount_skel.d
	$(DC) -o $@ $^

clean:
	-rm -f operators refcount_skel
