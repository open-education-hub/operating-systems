BINARY = alloc_size
include ../../../../../common/makefile/single.mk

DC = gdc

d_memory_alloc: d_memory_alloc.d
	$(DC) -o $@ $?

clean::
	-rm -f d_memory_alloc
