#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

source graded_test.inc.sh

# Call open with O_CREAT, check that open and close calls succeed and that the file is created
test_open_close_create_file()
{
    exec_file=./io/open_close_create_file

    if test ! -f "$exec_file"; then
        echo "No such file $exec_file" 1>&2
        exit 1
    fi

    nm "$exec_file" > /dev/null 2>&1
    if test $? -ne 0; then
        echo "No symbols in file" 1>&2
        exit 1
    fi

    nm "$exec_file" | grep ' open$' > /dev/null
    if test $? -ne 0; then
        echo "No open symbol" 1>&2
        exit 1
    fi

    "$exec_file"
    if test $? -ne 0; then
        rm -f ./create_file
        exit 1
    fi

    ls ./create_file >/dev/null        # check that file was created
    if test $? -ne 0; then
        exit 1
    fi

    rm -f ./create_file                    # remove file

    exit 0
}

# Open file, read content and write to stdout.
test_open_close_read_byte()
{
    exec_file=./io/open_close_read_byte

    if test ! -f "$exec_file"; then
        echo "No such file $exec_file" 1>&2
        exit 1
    fi

    nm "$exec_file" > /dev/null 2>&1
    if test $? -ne 0; then
        echo "No symbols in file" 1>&2
        exit 1
    fi

    nm "$exec_file" | grep ' open$' > /dev/null
    if test $? -ne 0; then
        echo "No open symbol" 1>&2
        exit 1
    fi

    echo "a" > "./existent_file"                         # create file
    diff -u <("$exec_file") <(echo "a")        # check read data

    if test $? -ne 0; then
        rm -f ./existent_file
        exit 1
    fi

    rm -f ./existent_file                                # remove file
    exit 0
}

run_test test_open_close_create_file 10
run_test test_open_close_read_byte 10
