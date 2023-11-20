SRC_PATH ?= ../src
UTILS_PATH = $(realpath ../utils)

.PHONY: all src check lint clean

all: src

src:
	make -C $(SRC_PATH) UTILS_PATH=$(UTILS_PATH)

check: clean
	make -i SRC_PATH=$(SRC_PATH)
	SRC_PATH=$(SRC_PATH) python checker.py

lint:
	-cd $(SRC_PATH)/.. && checkpatch.pl -f src/*.c
	-cd $(SRC_PATH)/.. && cpplint --recursive src/
	-cd $(SRC_PATH)/.. && shellcheck tests/*.sh
	-cd $(SRC_PATH)/.. && pylint tests/*.py

clean:
	make -C $(SRC_PATH) clean
	-rm -f *~
