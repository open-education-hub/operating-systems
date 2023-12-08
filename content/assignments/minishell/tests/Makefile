SRC_PATH ?= ../src

SOURCEDIR = src
BUILDDIR = bin
SRCS = $(sort $(wildcard $(SOURCEDIR)/*.c))
BINS = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%, $(SRCS))

.PHONY: all clean src check lint

all: src

src:
	make -C $(SRC_PATH) UTIL_PATH=$(shell pwd)/../util CPPFLAGS=-I$(shell pwd)/../src

check:
	make -C $(SRC_PATH) UTIL_PATH=$(shell pwd)/../util clean
	make clean
	make -i SRC_PATH=$(SRC_PATH)
	SRC_PATH=$(SRC_PATH) ./run_all.sh

lint:
	-cd .. && checkpatch.pl -f src/*.c
	-cd .. && cpplint --recursive src/
	-cd .. && shellcheck checker/*.sh
	-cd .. && shellcheck tests/*.sh
	-cd .. && shellcheck tests/_test/*.sh

clean:
	-rm -f *~
