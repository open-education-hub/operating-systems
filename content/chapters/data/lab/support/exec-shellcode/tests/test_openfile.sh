#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

source graded_test.inc.sh

shellcode=./openfile

if test -z "$SRC_PATH"; then
    SRC_PATH=../src
fi

test_openfile()
{
    if test ! -f "$shellcode"; then
        echo "No such file $shellcode" 1>&2
        exit 1
    fi

    objdump -D -M intel -b binary -m i386:x86-64 "$shellcode" > /dev/null 2>&1
    if test $? -ne 0; then
        echo "Incorrect shellcode file" 1>&2
        exit 1
    fi

    timeout -k 1 3 "$SRC_PATH"/exec_shellcode "$shellcode" > /dev/null 2>&1
    if test $? -ne 0; then
        echo "Program runs unsuccessfully" 1>&2
        exit 1
    fi

    test -f "uberfile" > /dev/null 2>&1
    if test $? -ne 0; then
        echo "File not created" 1>&2
        exit 1
    fi

    test "$(stat --format="%s" "uberfile")" -eq 0
    if test $? -ne 0; then
        echo "File is not truncated" 1>&2
        exit 1
    fi

    test "$(stat --format="%a" "uberfile")" = "644"
    if test $? -ne 0; then
        echo "File permissions not correctly set" 1>&2
        exit 1
    fi

    exit 0
}

run_test test_openfile 25
