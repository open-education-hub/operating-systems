LDLIBS = -lstdc++

.PHONY: all clean

all: memory_leak memory_leak_malloc

memory_leak: memory_leak.o

memory_leak.o: memory_leak.cpp

memory_leak_malloc: memory_leak_malloc.o

memory_leak_malloc.o: memory_leak_malloc.c

clean:
	-rm -f memory_leak memory_leak.o
	-rm -f memory_leak_malloc memory_leak_malloc.o
	-rm -f *~
