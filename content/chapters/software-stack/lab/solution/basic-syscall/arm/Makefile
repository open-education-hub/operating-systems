CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
LDFLAGS = -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none
QEMU = qemu-aarch64

.PHONY: all clean

all: hello

hello: hello.o

hello.o: hello.s

run: hello
	$(QEMU) ./hello

clean:
	-rm -f hello.o hello
	-rm -f *~
