LIBC_PATH ?= ../libc
CPPFLAGS = -nostdinc -I. -I$(LIBC_PATH)/include
CFLAGS = -Wall -Wextra -fno-PIC -fno-stack-protector -fno-builtin
# Remove the line below to disable debugging support.
CFLAGS += -g -O0
LDFLAGS = -nostdlib -no-pie -L$(LIBC_PATH)
LDLIBS = -lc

SRCS = $(wildcard test_*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXECS = $(patsubst %.c,%,$(SRCS))


.PHONY: all clean libc io memory process check

all: libc io memory process $(EXECS)

$(EXECS): %:%.o graded_test.o | libc
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJS): %.o:%.c graded_test.h

graded_test.o: graded_test.c graded_test.h

io:
	make -C io LIBC_PATH=../$(LIBC_PATH)

memory:
	make -C memory LIBC_PATH=../$(LIBC_PATH)

process:
	make -C process LIBC_PATH=../$(LIBC_PATH)

libc:
	make -C $(LIBC_PATH)

check:
	make -C $(LIBC_PATH) clean
	make clean
	make -i LIBC_PATH=$(LIBC_PATH)
	./run_all_tests.sh

clean:
	make -C io clean
	make -C memory clean
	make -C process clean
	-rm -f *~
	-rm -f graded_test.o $(OBJS)
	-rm -f $(EXECS)
