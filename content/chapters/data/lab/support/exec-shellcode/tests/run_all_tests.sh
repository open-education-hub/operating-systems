#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

if test -z "$SRC_PATH"; then
    SRC_PATH=../src
fi

export SRC_PATH

(
./test_helloworld.sh
./test_getpid.sh
./test_openfile.sh
./test_brk.sh
) | tee results.txt

total=$(grep '\( passed \| failed \)' results.txt | rev | cut -d ' ' -f 1 | rev | paste -s -d'+' | bc)
echo ""
echo -n "Total:                           "
echo -n "                                "
LC_ALL=C printf "%3d/100\n" "$total"

rm results.txt
