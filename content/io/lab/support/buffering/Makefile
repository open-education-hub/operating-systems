BINARIES=printf_buffering no_buffering libc_buffering diy_buffering
include ../../../../../common/makefile/multiple.mk

test-file:
	dd if=/dev/urandom of=test-file.txt bs=1024 count=1K

clean::
	rm -f *.txt
