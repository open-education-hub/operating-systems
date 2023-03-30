SRC_PATH ?= ../src
CC = gcc
CPPFLAGS = -I../utils -I $(SRC_PATH)
CFLAGS = -fPIC -Wall -Wextra -g
LDFLAGS = -L$(SRC_PATH)
LDLIBS = -losmem

SOURCEDIR = src
BUILDDIR = bin
SRCS = $(sort $(wildcard $(SOURCEDIR)/*.c))
BINS = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%, $(SRCS))

.PHONY: all clean src check lint

all: src $(BUILDDIR) $(BINS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/%: $(SOURCEDIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

src:
	make -C $(SRC_PATH)

check:
	make -C $(SRC_PATH) clean
	make clean
	make -i SRC_PATH=$(SRC_PATH)
	SRC_PATH=$(SRC_PATH) python checker.py

lint:
	-cd .. && checkpatch.pl -f src/*.c tests/src/*.c
	-cd .. && checkpatch.pl -f checker/*.sh
	-cd .. && cpplint --recursive src/ tests/ checker/
	-cd .. && shellcheck checker/*.sh
	-cd .. && pylint tests/*.py

clean:
	-rm -f *~
	-rm -f $(BINS)
