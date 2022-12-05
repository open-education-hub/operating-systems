BINARY = mmap_cp
include ../../../../../common/makefile/single.mk

large-file:
	dd if=/dev/urandom of=large-file.txt bs=1024 count=1M

test-file:
	dd if=/dev/urandom of=test-file.txt bs=1024 count=1K

clean::
	-rm -f *.txt
