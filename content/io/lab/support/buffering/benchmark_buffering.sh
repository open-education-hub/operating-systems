#! /bin/bash

FILE_NAME="test-file.txt"

drop_caches() {
	sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches";
}

test_operation() {
	echo "Testing $1 $2...";
	drop_caches;
	./"$1" "$2" $FILE_NAME;
}

test_buffering() {
	echo "======== Testing $1 ========";
	test_operation "$1" "read";
	test_operation "$1" "write";
}

make

[ -f test-file.txt ] || make test-file

if [ $# -lt 2 ]; then
	echo "Usage: $0 [no_buffering] [libc_buffering] [diy_buffering]"
	echo "Choose at least two of the three options."
	exit 1
fi

for i in "$@"; do
	if [ "$i" == "no_buffering" ] || [ "$i" == "libc_buffering" ] || [ "$i" == "diy_buffering" ]; then
		test_buffering "$i";
	else
		echo "Unknown option: $i"
	fi
done
