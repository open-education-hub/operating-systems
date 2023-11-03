export SRC_PATH ?= $(realpath ../src)
export UTILS_PATH ?= $(realpath ../utils)

CC = gcc
CPPFLAGS = -I$(UTILS_PATH)
CFLAGS = -fPIC -Wall -Wextra -g
LDFLAGS = -L$(SRC_PATH)
LDLIBS = -losmem

SNIPPETS_SRC = $(sort $(wildcard snippets/*.c))
SNIPPETS = $(patsubst %.c,%,$(SNIPPETS_SRC))

.PHONY: all src snippets clean_src clean_snippets check lint

all: src snippets

src:
	$(MAKE) -C $(SRC_PATH)

snippets: $(SNIPPETS)

clean_snippets:
	rm -rf $(SNIPPETS)

clean_src:
	$(MAKE) -C $(SRC_PATH) clean

check:
	$(MAKE) clean_src clean_snippets src snippets
	python3 run_tests.py

check-fast:
	$(MAKE) clean_src clean_snippets src snippets
	python3 run_tests.py -d

lint:
	-cd .. && checkpatch.pl -f src/*.c tests/snippets/*.c
	-cd .. && checkpatch.pl -f checker/*.sh tests/*.sh
	-cd .. && cpplint --recursive src/ tests/
	-cd .. && shellcheck checker/*.sh tests/*.sh
#	-cd .. && pylint tests/*.py

snippets/%: snippets/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
