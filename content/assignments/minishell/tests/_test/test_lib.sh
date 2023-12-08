#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

# ----------------- General declarations and util functions ------------------ #

# Enable/disable exiting when program fails.
EXIT_IF_FAIL=0
# Enable/disable debug (1/0).
DEBUG_=0

DEBUG()
{
    if test "$DEBUG_" = "1"; then
        "$@" 1>&2
    fi
}

print_header()
{
    header="${1}"
    header_len=${#header}
    printf "\n"
    if [ "$header_len" -lt 71 ]; then
        padding=$(((71 - header_len) / 2))
        for ((i = 0; i < padding; i++)); do
            printf " "
        done
    fi
    printf "= %s =\n\n" "${header}"
}


test_do_fail()
{
    printf "failed  [ 0/%02d]\n" "$max_points"
    if test "$EXIT_IF_FAIL" = "1"; then
        exit 1
    fi
}

test_do_pass()
{
    printf "passed  [%02d/%02d]\n" "$points" "$max_points"
}


DF=${DF:--BEbwu}

# Compares to files and prints the first 10
# lines if the files differ.
function compare()
{
    diff "$DF" "$1" "$2" > __result
    ret=$?
    if [ $ret != 0 ] ; then
        echo "$1 vs $2:"
        head -n 10 < __result
    fi
    rm -f __result
    return $ret
}

basic_test()
{
    DEBUG echo "TEST:" "$@"
    printf "%02d) %s" $(("$test_index"+1)) "$description"

    for ((i = 0; i < 56 - ${#description}; i++)); do
        printf "."
    done

    "$@" > /dev/null 2>&1
    if test $? -eq 0; then
        test_do_pass "$points"
    else
        test_do_fail "$points"
    fi
}

check_tests()
{
    # We need to have the test_fun_array defined.
    if [ -z "$test_fun_array" ]; then
        echo "test_fun_array is not defined - don't know what to run" 1>&2
        exit 1
    fi

    # Check max_points.
    if [ -z "$max_points" ]; then
        echo "max_points is not defined - don't the total number of points" 1>&2
        exit 1
    fi
}

run_tests()
{
    if test $# -ne 1; then
        echo "Usage: $0 test_number | init | cleanup" 1>&2
        exit 1
    fi

    test_index=$1

    if test "$test_index" == "init"; then
        init_world
        exit 0
    fi

    if test "$test_index" == "cleanup"; then
        cleanup_world
        exit 0
    fi

    if test "$test_index" == "check"; then
        check_source
        exit 0
    fi

    arr_index=$((test_index * 3))
    last_test=$((${#test_fun_array[@]} / 3))
    description=${test_fun_array[(($arr_index + 1))]}
    points=${test_fun_array[(($arr_index + 2))]}

    if test "$test_index" -gt "$last_test" -o "$arr_index" -lt 0; then
        echo "Error: Test index is out range (1 < test_index <= $last_test)." 1>&2
        exit 1
    fi

    # Run proper function.
    ${test_fun_array[(($arr_index))]}
}
