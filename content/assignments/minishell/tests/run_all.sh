#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

first_test=0
last_test=18
script=./_test/run_test.sh

exec_name="mini-shell"
if test -z "$SRC_PATH"; then
    SRC_PATH=$(pwd)/../src
fi
ln -fn "$SRC_PATH"/"$exec_name" .

# Call init to set up testing environment.
bash "$script" init

# Check the source (disabled, part of tests now).
# bash "$script" check.

for i in $(seq $first_test $last_test); do
    bash "$script" "$i"
done | tee results.txt

grep -a '\[.*\]$' results.txt | awk -F '[] /[]+' '
BEGIN {
    sum=0
}

{
	sum += $(NF-2);
}

END {
    printf "\n%66s  %3d/100\n", "Total:", sum;
}'

# Cleanup testing environment.
bash "$script" cleanup
rm -f results.txt
