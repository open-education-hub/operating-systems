SRC_PATH ?= ../src

.PHONY: all _test src check lint clean

all: src _test

_test:
	make -C $@ SRC_PATH=../$(SRC_PATH)

src:
	make -C $(SRC_PATH)

check: _test
	make -C $(SRC_PATH) clean
	make clean
	make -i SRC_PATH=$(SRC_PATH)
	SRC_PATH=$(SRC_PATH) ./run_all.sh

lint:
	-cd .. && checkpatch.pl -f src/*.c src/*.h src/samples/*.c src/utils/*.c src/utils/*.h tests/_test/*.c
	-cd .. && checkpatch.pl -f checker/*.sh tests/*.sh tests/_test/*.sh
	-cd .. && cpplint --recursive src/ tests/ checker/
	-cd .. && shellcheck checker/*.sh tests/*.sh tests/_test/*.sh

clean:
	-make -C _test SRC_PATH=../$(SRC_PATH) clean
	-make -C $(SRC_PATH) clean
	-rm -f aws
	-rm -f _log
	-rm -f *~
