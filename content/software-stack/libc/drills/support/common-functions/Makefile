NASM = nasm
CC = gcc
CFLAGS = -fno-PIC -fno-stack-protector
LDFLAGS = -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none

.PHONY: all clean

all: main_string main_printf

main_string: main_string.o string.o syscall.o

main_string.o: main_string.c syscall.h string.h

main_printf: main_printf.o printf.o string.o syscall.o

main_printf.o: main_printf.c printf.h syscall.h string.h

printf.o: printf.c printf.h

string.o: string.c string.h

syscall.o: syscall.s
	$(NASM) -f elf64 -o $@ $<

clean:
	-rm -f main_string main_printf
	-rm -f *.o
	-rm -f *~
