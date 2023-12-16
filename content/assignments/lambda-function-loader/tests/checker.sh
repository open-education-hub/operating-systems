#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

#
# Checker script for SO Hackathon December 2023
#

set -eu

# paths / constants
CHECKER_SCRIPT=$(realpath "$0")
CHECKER_DIR=$(dirname "${CHECKER_SCRIPT}")
CHECKER_MAKEFILE="${CHECKER_DIR}/Makefile"
REF_DIR="${CHECKER_DIR}/ref"
BIG_DIR="${REF_DIR}/big"
ROOT_DIR=$(dirname "${CHECKER_DIR}")
SOLUTION_DIR="${ROOT_DIR}/src"
SOLUTION_MAKEFILE="${SOLUTION_DIR}/Makefile"

MAKE_OUTPUT=$(mktemp -u "${CHECKER_DIR}/make.XXXXXX")
SERVER_OUT_DIR="${CHECKER_DIR}/output"
SERVER_OUTPUT="${SERVER_OUT_DIR}/server.out"
CLIENT_OUT_DIR="${CHECKER_DIR}/output"

SERVER_BIN="${SOLUTION_DIR}/server"
CLIENT_BIN="${CHECKER_DIR}/client"

SERVER_PID=""

PADDING_LEN=40
TOTAL_SCORE=0
MAX_TOTAL_SCORE=100

# Colors for colored output
COLOR_RED="\x1b[1;31m"
COLOR_GREEN="\x1b[1;32m"
COLOR_YELLOW="\x1b[1;33m"
COLOR_RESET="\x1b[0m"

# Export LD_LIBRARY_PATH to inform the dynamic loader where it should look for the libraries
export LD_LIBRARY_PATH="${SOLUTION_DIR}:${LD_LIBRARY_PATH:-}"

# Cleanup if required
trap 'rm -f "${MAKE_OUTPUT}"; kill_server' EXIT ERR TERM INT

err() {
    echo "$@" >&2
}

gen_err_test() {
    mkdir -p "$REF_DIR"

    echo "Error: $CHECKER_DIR/libfictional.so solve all_my_problems could not be executed." > "$REF_DIR/test5"
    echo "Error: $CHECKER_DIR/libbasic.so solve all_my_problems could not be executed." > "$REF_DIR/test6"
}

# arg: number_of_clients
gen_big_test() {
    _NUMBER_OF_CLIENTS=$1

    mkdir -p "$BIG_DIR"
    GEN_REF_FILE="$REF_DIR/test9"

    if [[ "$(ls "$BIG_DIR" | wc -l)" -ne $((_NUMBER_OF_CLIENTS/4)) ]]; then
        # echo "Generating..."
        rm -rf "${BIG_DIR:?}/*"
        rm -f "$GEN_REF_FILE"

        for i in $(seq 1 4 "$_NUMBER_OF_CLIENTS")
        do
            head -c 128 </dev/urandom > "$BIG_DIR/test_$i"
        done
    fi

    GEN_REF_FILE="$REF_DIR/test9"

    rm -f "$GEN_REF_FILE"

    for CLIENT_NUM in $(seq 1 "${_NUMBER_OF_CLIENTS}"); do
        if [ $((CLIENT_NUM%4)) -eq 0 ]; then
            echo "Got called 1 times, cool!" >> "$GEN_REF_FILE"
        elif [ $((CLIENT_NUM%4)) -eq 1 ]; then
            cat "${BIG_DIR}/test_${CLIENT_NUM}" >> "$GEN_REF_FILE"
        elif [ $((CLIENT_NUM%4)) -eq 2 ]; then
            echo "Reseted the counter!" >> "$GEN_REF_FILE"
        else
            echo "Error: $CHECKER_DIR/libfictional.so reset could not be executed." >> "$GEN_REF_FILE"
        fi
    done
}

make_sources() {
    if ! make -C "${SOLUTION_DIR}" -f "${SOLUTION_MAKEFILE}" >& "${MAKE_OUTPUT}"; then
        err "Could not build solution sources"
        err "Review error messages below"
        err "---------------------------------"
        cat "${MAKE_OUTPUT}"
        exit 1
    fi
}

make_checker() {
    if ! make -C "${CHECKER_DIR}" -f "${CHECKER_MAKEFILE}" >& "${MAKE_OUTPUT}"; then
        err "Could not build checker"
        err "Review error messages below"
        err "---------------------------------"
        cat "${MAKE_OUTPUT}"
        exit 1
    fi
}

make_all() {
    make_sources
    make_checker
}

# test helper functions
start_server() {
    mkdir -p "${SERVER_OUT_DIR}"
    nohup "${SERVER_BIN}" >& "${SERVER_OUTPUT}" &
    SERVER_PID=$!
    # echo "Starting server"
}

kill_server() {
    if [ -z "${SERVER_PID}" ] || ! kill -0 "${SERVER_PID}" 2> /dev/null; then
        # err "Invalid server PID; cannot kill"
        return
    fi

    # echo -e "\nKilling server"
    kill "${SERVER_PID}"
}

_delay() {
    sleep 0.25
}

fail() {
    printf "${COLOR_RED}%s${COLOR_RESET}\n" "$*"
}

pass() {
    printf "${COLOR_GREEN}%s${COLOR_RESET}\n" "$*"
}

print_yellow() {
    printf "${COLOR_YELLOW}%s${COLOR_RESET}\n" "$*"
}


# arg1: test number
# arg2: test name
print_running_test() {
    printf "Running test %+2s: %-${PADDING_LEN}s" "$1" "$2"
}

# arg1: result
# arg2: max points
# arg3: comment
print_test_result() {
    printf "[%+3s/%+3s] " "$1" "$2"
    if [[ ! "$1" -eq 0 ]]; then
        pass "$3"
    else
        fail "$3"
    fi
}

start_server_per_test() {
    if [[ -v SERVER_DEBUG && $SERVER_DEBUG -eq 1 ]]; then
        start_server
        _delay
    fi
}

start_server_once() {
    if [[ ! -v SERVER_DEBUG || $SERVER_DEBUG -ne 1 ]]; then
        start_server
        _delay
    fi
}

kill_server_per_test() {
    if [[ -v SERVER_DEBUG && $SERVER_DEBUG -eq 1 ]]; then
        kill_server
    fi
}

kill_server_once() {
    if [[ ! -v SERVER_DEBUG || $SERVER_DEBUG -ne 1 ]]; then
        kill_server
    fi
}

test_simple_response() {
    local OUTPUT_FILE="$1"

    if [[ "$(cat "$OUTPUT_FILE" | wc -w)" -le 0 ]]; then
        echo "No response"
    fi
}

test_output_exists() {
    local OUTPUT_FILE="$1"

    if [[ "$(cat "$OUTPUT_FILE" | wc -w)" -le 0 ]]; then
        echo "No response"
    elif [[ ! -f "$(head -n1 "${OUTPUT_FILE}")" ]]; then
        echo "Output file ($(head -n1 "${OUTPUT_FILE}")) does not exist"
    fi
}

test_output_with_ref() {
    local OUTPUT_FILE="$1"
    local REF_FILE="$2"

    local AGGREGATE_OUT
    AGGREGATE_OUT=$(mktemp "$OUTPUT_FILE.XXXXXX")

    if [ "$(cat "$OUTPUT_FILE" | wc -w)" -le 0 ]; then
        echo "No response"
    elif [ ! -f "$(head -n1 "${OUTPUT_FILE}")" ]; then
        echo "Output file ($(head -n1 "${OUTPUT_FILE}")) does not exist"
    else
        while read -r LINE;
        do
            cat "$LINE" >> "$AGGREGATE_OUT"
        done < "$OUTPUT_FILE";

        if ! diff -q "${AGGREGATE_OUT}" "${REF_FILE}" > /dev/null; then
            echo "Output from server (${AGGREGATE_OUT}) differs from reference (${REF_FILE})"
        else
            rm "$AGGREGATE_OUT"
        fi
    fi
}

# args:
# test_number test_name test_score lib.so [fn_name [arg]]
test_harness() {
    if [ $# -lt 3 ]; then
        echo "Invalid test arguments"
        return
    fi

    _TEST_NUMBER=$1
    _TEST_NAME=$2
    _TEST_SCORE=$3
    _TEST_CHECK_OP=$4
    _CLIENT_COUNT=$5
    _LIB_NAME=$6
    _FN_NAME=${7:-}
    _ARG=${8:-}

    CLIENT_FAIL_COUNT=0

    start_server_per_test
    print_running_test "$_TEST_NUMBER" "$_TEST_NAME"

    THIS_TEST_SCORE=0
    # LIB_PATH=$(realpath "$_LIB_NAME")
    REF_FILE="${REF_DIR}/test$_TEST_NUMBER"

    unset CLIENT_PIDS
    declare -A CLIENT_PIDS

    for CLIENT_NUM in $(seq 1 "${_CLIENT_COUNT}"); do
        CLIENT_OUTPUT="${CLIENT_OUT_DIR}/test$_TEST_NUMBER-$CLIENT_NUM.out"
        CLIENT_OUTPUT_ERR="${CLIENT_OUT_DIR}/test$_TEST_NUMBER-$CLIENT_NUM.err"
        # Run client with the given arguments - arguments 5 and 6 must be unquoted,
        # since they can be empty
        # The clients must not receive the full path because then the server will get
        # a command (that will have to write to the file in case of error)
        # The client binary will always be in the same directory as the library.
        timeout 5s "${CLIENT_BIN}" "$_LIB_NAME" "$_FN_NAME" "$_ARG" 1> "${CLIENT_OUTPUT}" 2> "${CLIENT_OUTPUT_ERR}" &

        CLIENT_PIDS[$CLIENT_NUM]=$!
    done

    CLIENT_AGGREGATE_OUT="${CLIENT_OUT_DIR}/test$_TEST_NUMBER.out"
    CLIENT_AGGREGATE_ERR="${CLIENT_OUT_DIR}/test$_TEST_NUMBER.err"
    echo -n > "${CLIENT_AGGREGATE_OUT}"
    echo -n > "${CLIENT_AGGREGATE_ERR}"

    for CLIENT_NUM in "${!CLIENT_PIDS[@]}"; do
        if ! wait "${CLIENT_PIDS[$CLIENT_NUM]}"; then
            : $((CLIENT_FAIL_COUNT++))
        fi
    done

    if [ ${CLIENT_FAIL_COUNT} -ne 0 ]; then
        print_test_result 0 "$_TEST_SCORE" "${CLIENT_FAIL_COUNT} clients have failed"
        kill_server_per_test
        return
    fi

    for CLIENT_NUM in "${!CLIENT_PIDS[@]}"; do
        CLIENT_OUTPUT="${CLIENT_OUT_DIR}/test$_TEST_NUMBER-$CLIENT_NUM.out"
        CLIENT_OUTPUT_ERR="${CLIENT_OUT_DIR}/test$_TEST_NUMBER-$CLIENT_NUM.err"

        if grep -q "Output file:" "${CLIENT_OUTPUT}"; then
            OUTPUT_FILE=$(awk '{ print $3 }' "${CLIENT_OUTPUT}")
            echo "${OUTPUT_FILE}" >> "${CLIENT_AGGREGATE_OUT}"
        fi

        cat "${CLIENT_OUTPUT_ERR}" >> "${CLIENT_AGGREGATE_ERR}"
    done

    if [ -s "${CLIENT_AGGREGATE_ERR}" ]; then
        print_test_result 0 "$_TEST_SCORE" "Client errors"
        kill_server_per_test
        return
    fi

    TEST_CHECK_RESULT=$("${_TEST_CHECK_OP}" "${CLIENT_AGGREGATE_OUT}" "${REF_FILE}")
    if [ -z "${TEST_CHECK_RESULT}" ]; then
        print_test_result "$_TEST_SCORE" "$_TEST_SCORE" "Test passed"
        THIS_TEST_SCORE=$_TEST_SCORE
    else
        print_test_result 0 "$_TEST_SCORE" "${TEST_CHECK_RESULT}"
    fi

    TOTAL_SCORE=$((TOTAL_SCORE+THIS_TEST_SCORE))

    kill_server_per_test
}

# args:
# test_number test_name test_score lib.so [fn_name [arg]]
big_test() {
    if [ $# -lt 3 ]; then
        echo "Invalid test arguments"
        return
    fi

    _TEST_NUMBER=$1
    _TEST_NAME=$2
    _TEST_SCORE=$3
    _TEST_CHECK_OP=$4
    _CLIENT_COUNT=$5

    CLIENT_FAIL_COUNT=0

    start_server_per_test
    print_running_test "$_TEST_NUMBER" "$_TEST_NAME"

    THIS_TEST_SCORE=0
    REF_FILE="${REF_DIR}/test$_TEST_NUMBER"

    unset CLIENT_PIDS
    declare -A CLIENT_PIDS

    for CLIENT_NUM in $(seq 1 "${_CLIENT_COUNT}"); do
        CLIENT_OUTPUT="${CLIENT_OUT_DIR}/test$_TEST_NUMBER-$CLIENT_NUM.out"
        CLIENT_OUTPUT_ERR="${CLIENT_OUT_DIR}/test$_TEST_NUMBER-$CLIENT_NUM.err"
        # Run client with the given arguments - arguments 5 and 6 must be unquoted,
        # since they can be empty
        # The clients must not receive the full path because then the server will get
        # a command (that will have to write to the file in case of error)
        # The client binary will always be in the same directory as the library.

        if [ $((CLIENT_NUM%4)) -eq 0 ]; then
            timeout 5s "${CLIENT_BIN}" "${CHECKER_DIR}/libspecial.so" \
                1> "${CLIENT_OUTPUT}" 2> "${CLIENT_OUTPUT_ERR}" &
        elif [ $((CLIENT_NUM%4)) -eq 1 ]; then
            timeout 5s "${CLIENT_BIN}" "${CHECKER_DIR}/libbasic.so" "cat" "${BIG_DIR}/test_${CLIENT_NUM}" \
                1> "${CLIENT_OUTPUT}" 2> "${CLIENT_OUTPUT_ERR}" &
        elif [ $((CLIENT_NUM%4)) -eq 2 ]; then
            timeout 5s "${CLIENT_BIN}" "${CHECKER_DIR}/libspecial.so" "reset" \
                1> "${CLIENT_OUTPUT}" 2> "${CLIENT_OUTPUT_ERR}" &
        else
            # -eq 3
            timeout 5s "${CLIENT_BIN}" "${CHECKER_DIR}/libfictional.so" "reset" \
                1> "${CLIENT_OUTPUT}" 2> "${CLIENT_OUTPUT_ERR}" &
        fi
        CLIENT_PIDS[$CLIENT_NUM]=$!
    done

    CLIENT_AGGREGATE_OUT="${CLIENT_OUT_DIR}/test$_TEST_NUMBER.out"
    CLIENT_AGGREGATE_ERR="${CLIENT_OUT_DIR}/test$_TEST_NUMBER.err"
    echo -n > "${CLIENT_AGGREGATE_OUT}"
    echo -n > "${CLIENT_AGGREGATE_ERR}"

    for CLIENT_NUM in "${!CLIENT_PIDS[@]}"; do
        if ! wait "${CLIENT_PIDS[$CLIENT_NUM]}"; then
            : $((CLIENT_FAIL_COUNT++))
        fi
    done

    if [[ ${CLIENT_FAIL_COUNT} -ne 0 ]]; then
        print_test_result 0 "$_TEST_SCORE" "${CLIENT_FAIL_COUNT} clients have failed"
        kill_server_per_test
        return
    fi

    for CLIENT_NUM in $(seq 1 "${_CLIENT_COUNT}"); do
        CLIENT_OUTPUT="${CLIENT_OUT_DIR}/test$_TEST_NUMBER-$CLIENT_NUM.out"
        CLIENT_OUTPUT_ERR="${CLIENT_OUT_DIR}/test$_TEST_NUMBER-$CLIENT_NUM.err"

        if grep -q "Output file:" "${CLIENT_OUTPUT}"; then
            OUTPUT_FILE=$(awk '{ print $3 }' "${CLIENT_OUTPUT}")
            echo "${OUTPUT_FILE}" >> "${CLIENT_AGGREGATE_OUT}"
        fi

        cat "${CLIENT_OUTPUT_ERR}" >> "${CLIENT_AGGREGATE_ERR}"
    done

    if [ -s "${CLIENT_AGGREGATE_ERR}" ]; then
        print_test_result 0 "$_TEST_SCORE" "Client errors"
        kill_server_per_test
        return
    fi

    TEST_CHECK_RESULT=$("${_TEST_CHECK_OP}" "${CLIENT_AGGREGATE_OUT}" "${REF_FILE}")
    if [ -z "${TEST_CHECK_RESULT}" ]; then
        print_test_result "$_TEST_SCORE" "$_TEST_SCORE" "Test passed"
        THIS_TEST_SCORE=$_TEST_SCORE
    else
        print_test_result 0 "$_TEST_SCORE" "${TEST_CHECK_RESULT}"
    fi

    TOTAL_SCORE=$((TOTAL_SCORE+THIS_TEST_SCORE))

    kill_server_per_test
}

bad_input() {
    err "Bad input (maybe test number out of bounds?)"
    err "Run like ./checker"
    err "         or"
    err "         ./checker <test_number>"
    err "         or"
    err "         SERVER_DEBUG=1 bash checker.sh # to have your server restared for each test"
}

# actual tests
run_tests() {
    if [[ -v SERVER_DEBUG && $SERVER_DEBUG -eq 1 ]]; then
        echo "Running the checker with server restart per test"
    fi

    start_server_once

    TESTS=(

    'test_harness         1 "Basic response"               5 test_simple_response 1    "${CHECKER_DIR}/libbasic.so"'
    'test_harness         2 "Basic file"                   5 test_output_exists   1    "${CHECKER_DIR}/libbasic.so"'
    'test_harness         3 "Basic file content"           5 test_output_with_ref 1    "${CHECKER_DIR}/libbasic.so"'
    'test_harness         4 "Basic cat file content"      10 test_output_with_ref 1    "${CHECKER_DIR}/libbasic.so"      "cat"   "$CHECKER_DIR/client.c"'

    'test_harness         5 "Wrong library"               10 test_output_with_ref 1    "${CHECKER_DIR}/libfictional.so"  "solve" "all_my_problems"'
    'test_harness         6 "Wrong function"              10 test_output_with_ref 1    "${CHECKER_DIR}/libbasic.so"      "solve" "all_my_problems"'

    'test_harness         7 "Parallel calls"              15 test_output_with_ref 10   "${CHECKER_DIR}/libadvanced.so"   "sleepy"'
    'test_harness         8 "Parallel calls, but cooler"  15 test_output_with_ref 100  "${CHECKER_DIR}/libspecial.so"'

    'big_test             9 "Can you handle this?"        25 test_output_with_ref 1000'

    # Bonus tests
    'test_harness        10 "Clumsy pointers"             10 test_output_with_ref 1     "${CHECKER_DIR}/libadvanced.so"  "clumsy"'
    'test_harness        11 "Sleepy program"              10 test_output_with_ref 1     "${CHECKER_DIR}/libadvanced.so"  "going_to_sleep"'
    )

    FIRST_TEST=1
    LAST_TEST=${#TESTS[@]}

    if [[ $# -eq 1 ]]; then
        if [[ "$1" -le "$LAST_TEST" && "$1" -ge 1 ]]; then
            FIRST_TEST=$1
            LAST_TEST=$1
        else
            bad_input
            return
        fi
    elif [ $# -eq 0 ];then
        # is ok
        :
    else
        bad_input
        return
    fi

    for TEST_NO in $(seq "$FIRST_TEST" "$LAST_TEST")
    do

        if [[ $TEST_NO -eq 10 ]]; then
            print_yellow "### Bonus ###"
        fi

        eval "${TESTS[$((TEST_NO-1))]}"
    done

    # stop_server_once is taken care of by trap command
}

main() {
    make_all
    gen_err_test
    gen_big_test 1000
    run_tests "$@"

    if [[ $# -eq 0 ]]; then
        PADDING=$(printf '.%.0s' $(eval echo "{1..$((PADDING_LEN+6))}"))
        printf "Total Score%s[%+3s/%-3s]\n" "$PADDING" $TOTAL_SCORE $MAX_TOTAL_SCORE
    fi
}

main "$@"
