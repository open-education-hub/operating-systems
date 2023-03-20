#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

source graded_test.inc.sh

exec_file=./io/fstat

# Create file. Verify the following info: inode number, UID, GID, link count, number of blocks, size, last modify time
test_fstat()
{
    if test ! -f "$exec_file"; then
        echo "No such file $exec_file" 1>&2
        exit 1
    fi

    nm "$exec_file" > /dev/null 2>&1
    if test $? -ne 0; then
        echo "No symbols in file $exec_file" 1>&2
        exit 1
    fi

    nm "$exec_file" | grep ' fstat$' > /dev/null
    if test $? -ne 0; then
        echo "No fstat symbol" 1>&2
        exit 1
    fi

    touch ./existent_file         # create file

    diff -u <(stat --format="%i %u %g %h %b %s %Y" "./existent_file") <("$exec_file")
    if test $? -ne 0; then
        rm -f ./existent_file
        exit 1
    fi

    rm -f ./existent_file            # remove file
    exit 0
}

run_test test_fstat 10
