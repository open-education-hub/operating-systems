#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

#
# Print test result. Printed message should fit in 72 characters.
#
# Print format is:
#
# description ...................... passed ... NNN
# description ...................... failed ... NNN
#   32 chars        24 chars           6     3   3
#

print_test()
{
    func="$1"
    result="$2"
    points="$3"

    if test "$points" -gt 999; then
        points=999
    fi

    printf "%-32s " "${func:0:31}"
    printf "........................"
    if test "$result" -eq 0; then
        printf " passed ... %3d\n" "$points"
    else
        printf " failed ...  0\n"
    fi
}

run_test()
{
    func="$1"
    points="$2"

    # Run in subshell.
    (eval "$func")
    print_test "$func" "$?" "$points"
}
