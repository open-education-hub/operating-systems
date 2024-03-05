#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

source graded_test.inc.sh

exec_file=./io/puts

test_puts()
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

    nm "$exec_file" | grep ' puts$' > /dev/null
    if test $? -ne 0; then
        echo "No puts symbol" 1>&2
        exit 1
    fi

    "$exec_file" | grep 'Hello, World!' > /dev/null
    ret="$?"
    num_lines=$("$exec_file" | wc -l)

    if test "$ret" -ne 0 -o "$num_lines" -ne 1; then
        exit 1
    fi

    exit 0
}

run_test test_puts 15
