#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

source graded_test.inc.sh

exec_file=./io/truncate

# Truncate file to size 20, check that call succeeds, then check file size.
test_truncate()
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

    nm "$exec_file" | grep ' truncate$' > /dev/null
    if test $? -ne 0; then
        echo "No truncate symbol" 1>&2
        exit 1
    fi

    truncate -s 50 ./existent_file        # create file with size 50

    "$exec_file"
    if test $? -ne 0; then
        rm -f ./existent_file
        exit 1
    fi

    diff -u <(stat --format="%s" ./existent_file) <(echo 20)     # check that file size is 20
    if test $? -ne 0; then
        rm -f ./existent_file
        exit 1
    fi

    rm -f ./existent_file                    # remove file
    exit 0
}

run_test test_truncate 10
