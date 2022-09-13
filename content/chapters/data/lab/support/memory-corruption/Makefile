BINARY = c_segfault
include ../../../../../common/makefile/single.mk

DC = gdc

d_segfault: d_segfault.d
	$(DC) -o $@ $^

clean::
	-rm -f d_segfault
