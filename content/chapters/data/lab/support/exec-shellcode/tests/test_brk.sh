#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

source graded_test.inc.sh

shellcode=./brk

if test -z "$SRC_PATH"; then
    SRC_PATH=../src
fi

test_brk()
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

    timeout -k 1 3 strace "$SRC_PATH"/exec_shellcode "$shellcode" 2>&1 \
        | grep -A 1 close | tail -2 | grep 'brk(NULL)[ \t]\+= 0x' > /dev/null 2>&1
    if test $? -ne 0; then
        echo "brk not called correctly" 1>&2
        exit 1
    fi
    exit 0
}

run_test test_brk 25
