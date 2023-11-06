SRC_PATH ?= ../src
FULL_SRC_PATH = $(realpath $(SRC_PATH))
CPPFLAGS = -I. -I$(realpath $(SRC_PATH)) -I../utils
CFLAGS = -Wall -Wextra
# Remove the line below to disable debugging support.
CFLAGS += -g -O0

SRCS = $(wildcard *.asm)
SHELLCODES = $(patsubst %.asm,%,$(SRCS))

.PHONY: all src check lint clean

all: $(SHELLCODES) src

$(SHELLCODES): %:%.asm | src
	nasm -o $@ $<

src:
	make -C $(FULL_SRC_PATH)

check: $(SHELLCODES)
	make -C $(FULL_SRC_PATH) clean
	make clean
	make -i SRC_PATH=$(FULL_SRC_PATH)
	./run_all_tests.sh

lint:
	-cd .. && checkpatch.pl -f src/*.c
	-cd .. && checkpatch.pl -f tests/*.sh
	-cd .. && cpplint --recursive src/
	-cd .. && shellcheck tests/*.sh

clean:
	-rm -f *~
