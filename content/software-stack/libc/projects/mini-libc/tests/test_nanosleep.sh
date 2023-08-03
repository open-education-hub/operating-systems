#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

source graded_test.inc.sh

exec_file=./process/nanosleep

test_nanosleep()
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

    nm "$exec_file" | grep ' nanosleep$' > /dev/null
    if test $? -ne 0; then
        echo "No nanosleep symbol" 1>&2
        exit 1
    fi

    timeout -k 1 2 strace "$exec_file" 2>&1 > /dev/null | grep nanosleep > /dev/null
    if test $? -ne 0; then
        echo "No nanosleep syscall" 1>&2
        exit 1
    fi

    "$exec_file" &
    sleep 2
    pgrep -f '[p]rocess/nanosleep' > /dev/null
    if test $? -ne 0; then
        echo "No nanosleep process" 1>&2
        exit 1
    fi
    kill $!
    kill -9 $!

    exit 0
}

run_test test_nanosleep 20
