SRC_PATH ?= ../src
FULL_SRC_PATH = $(realpath $(SRC_PATH))
CPPFLAGS = -I. -I$(realpath $(SRC_PATH)) -I../utils
CFLAGS = -Wall -Wextra
# Remove the line below to disable debugging support.
CFLAGS += -g -O0

SRCS = $(wildcard test*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXECS = $(patsubst %.c,%,$(SRCS))


.PHONY: all src check lint clean

all: src $(EXECS)

$(EXECS): %:%.o graded_test.o $(SRC_PATH)/access_counter.o ../utils/log/log.o | src
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJS): %.o:%.c graded_test.h

graded_test.o: graded_test.c graded_test.h

../utils/log/log.o: ../utils/log/log.c ../utils/log/log.h

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
	-rm -f *~
	-rm -f graded_test.o $(OBJS)
	-rm -f $(EXECS)
