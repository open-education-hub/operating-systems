#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

source graded_test.inc.sh

exec_file=./io/lseek

# Create file of size 20, perform lseek operations, check returned offsets
test_lseek()
{
    if test ! -f "$exec_file"; then
        echo "No such file $exec_file" 1>&2
        exit 1
    fi

    nm "$exec_file" > /dev/null 2>&1
    if test $? -ne 0; then
        echo "No symbols in file" 1>&2
        exit 1
    fi

    nm "$exec_file" | grep ' lseek$' > /dev/null
    if test $? -ne 0; then
        echo "No lseek symbol" 1>&2
        exit 1
    fi

    truncate -s 20 "./existent_file"  # create file of size 20

    "$exec_file"
    if test $? -ne 0; then
        rm -f "./existent_file"
        exit 1
    fi

    rm -f "./existent_file"                                # remove file
    exit 0
}

run_test test_lseek 10
