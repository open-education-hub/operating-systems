#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

first_test=1
last_test=35
script=run_test.sh
timeout=30
log_file=test.log

exec_name="aws"
if test -z "$SRC_PATH"; then
    SRC_PATH=$(pwd)/../src
fi
ln -fn "$SRC_PATH"/"$exec_name" .

# Call init to set up testing environment.
timeout $timeout bash ./_test/"$script" init

for i in $(seq $first_test $last_test); do
    echo "=== Enter test $i ===" >> $log_file
    timeout $timeout bash ./_test/"$script" "$i" 2>> $log_file
    exit_code=$?
    echo "=== Exit test $i ===" >> $log_file
    if [ $exit_code -eq 124 ]; then
        printf "%02d) timeout............................................................failed  [00/90]\n" "$i"
    elif [ $exit_code -ne 0 ]; then
        printf "%02d) crash..............................................................failed  [00/90]\n" "$i"
    fi
done | tee results.txt

grep '\[.*\]$' results.txt | awk -F '[] /[]+' '
BEGIN {
    sum = 0
}

{
    sum += $(NF-2);
}

END {
    printf "\n%66s  %3d/100\n", "Total:", sum;
}'

# Cleanup testing environment.
timeout $timeout bash ./_test/"$script" cleanup
rm -f results.txt
