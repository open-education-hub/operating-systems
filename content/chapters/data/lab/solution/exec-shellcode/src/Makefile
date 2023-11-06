CFLAGS ?= -Wall -Wextra
CPPFLAGS ?= -I../utils

.PHONY: all clean

all: exec_shellcode

exec_shellcode: exec_shellcode.o ../utils/log/log.o

../utils/log/log.o: ../utils/log/log.c ../utils/log/log.h

clean:
	-rm -f exec_shellcode exec_shellcode
	-rm -f *~
