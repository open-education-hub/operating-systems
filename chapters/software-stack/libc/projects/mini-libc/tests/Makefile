SRC_PATH ?= ../src
FULL_SRC_PATH = $(realpath $(SRC_PATH))
CPPFLAGS = -nostdinc -I. -I$(FULL_SRC_PATH)/include
CFLAGS = -Wall -Wextra -fno-PIC -fno-stack-protector -fno-builtin
# Remove the line below to disable debugging support.
CFLAGS += -g -O0
LDFLAGS = -nostdlib -no-pie -L$(FULL_SRC_PATH)
LDLIBS = -lc

SRCS = $(wildcard test_*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXECS = $(patsubst %.c,%,$(SRCS))


.PHONY: all clean src io memory process check

all: src io memory process $(EXECS)

$(EXECS): %:%.o graded_test.o | src
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJS): %.o:%.c graded_test.h

graded_test.o: graded_test.c graded_test.h

io:
	make -C io SRC_PATH=$(FULL_SRC_PATH)

memory:
	make -C memory SRC_PATH=$(FULL_SRC_PATH)

process:
	make -C process SRC_PATH=$(FULL_SRC_PATH)

src:
	make -C $(FULL_SRC_PATH)

check:
	make -C $(FULL_SRC_PATH) clean
	make clean
	make -i SRC_PATH=$(FULL_SRC_PATH)
	./run_all_tests.sh

lint:
	-cd .. && checkpatch.pl -f src/*.c tests/*.c tests/*/*.c
	-cd .. && checkpatch.pl -f checker/*.sh tests/*.sh
	-cd .. && cpplint --recursive src/ tests/ checker/
	-cd .. && shellcheck checker/*.sh tests/*.sh

clean:
	make -C io clean
	make -C memory clean
	make -C process clean
	-rm -f *~
	-rm -f graded_test.o $(OBJS)
	-rm -f $(EXECS)
