NASM = nasm
ASFLAGS = -f elf64
CC = gcc
LDFLAGS = -no-pie
LDLIBS = -lpthread
BINARY = race_condition_lock

.PHONY: all clean

all: $(BINARY)

$(BINARY).o: $(BINARY).S
	$(NASM) $(ASFLAGS) -o $@ $<

clean:
	-rm -f $(BINARY) $(BINARY).o
	-rm -f *~
