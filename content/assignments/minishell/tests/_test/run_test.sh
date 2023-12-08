#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause
# shellcheck disable=SC2317
# shellcheck disable=SC2034

# ----------------- General declarations and util functions ------------------ #

exec_name=mini-shell
ref_name="bash"
ref_name_alt="dash"

MAIN_TEST_DIR="_test/outputs"
INPUT_DIR="_test/inputs"
REFS_DIR="_test/refs"
LOG_FILE="/dev/null"
export max_points=100
TEST_TIMEOUT=30

TEST_LIB=_test/test_lib.sh
export CHECK_SKIP='parser.\(\(tab\|yy\).\(c\|h\)\|h\)$'

# Load the lib functions.
if ! [ -e "$TEST_LIB" ]; then
	echo "Test library not found. Check \$TEST_LIB ($TEST_LIB)"
	exit 1
fi
# shellcheck source=tests/_test/test_lib.sh
source "$TEST_LIB"

export SHELL_PROMPT="> "

# Change this of you want to keep the logs after execution.
DO_CLEANUP=no

BUFFERING_WRAPPER=""
if command -v stdbuf &>/dev/null; then
	# stdbuf may not be installed on cygwin.
	BUFFERING_WRAPPER="stdbuf -i 0"
fi

USE_VALGRIND="${USE_VALGRIND:-yes}"
VALGRIND_LOG="valgrind.log"

# ----------------- Init and cleanup tests ----------------------------------- #

# Initializes a test.
init_test() {

	if ! [ -e "$exec_name" ]; then
		echo "$exec_name not found! Cannot run the test"
		exit 1
	fi

	if [ "$USE_VALGRIND" = "yes" ]; then
		if command -v valgrind &>/dev/null; then
			exec_name="valgrind --leak-check=full \
                --show-leak-kinds=all \
                --child-silent-after-fork=yes \
                --track-fds=yes \
                --log-file=$VALGRIND_LOG \
                $exec_name"
		else
			echo "valgrind is not installed."
		fi
	fi

	# Generates random file as test file.
	TEST_NAME=$(printf "test_%02d" $(("$test_index" + 1)))
	OUT_DIR="${TEST_NAME}_out"
	REF_DIR="${TEST_NAME}_ref"
	IN_FILE="${TEST_NAME}.in"
	REF_FILE="${TEST_NAME}.ref"
	OUT_FILE="${TEST_NAME}.out"

	local input_basename="${INPUT_DIR}/${TEST_NAME}"

	# Check if there is a platform specific input file.
	if [ -f "${input_basename}.${OS_PLATFORM}.txt" ]; then
		input_basename="${input_basename}.${OS_PLATFORM}"
	fi

	# Copy input files in the testing directory.
	cp "${input_basename}.txt" "${MAIN_TEST_DIR}/${IN_FILE}" &>"$LOG_FILE"
	# Copy additional files, if they exist (see test 04).
	# cp ${input_basename}?*.txt ${MAIN_TEST_DIR} &> $LOG_FILE
	# Copy any reference files, if they exist (see test 18).
	cp "${REFS_DIR}/${TEST_NAME}.ref" "${MAIN_TEST_DIR}" &>"$LOG_FILE"

	# Export mini-shell in path.
	PATH="$PATH:$(pwd)"
	cd "${MAIN_TEST_DIR}" || exit 1

	rm -rf "${OUT_DIR}"
	rm -rf "${REF_DIR}"
}

# Cleanups a test.
cleanup_test() {
	if [ "$DO_CLEANUP" = "yes" ]; then
		rm -rf "${OUT_DIR}"
		rm -rf "${REF_DIR}"
		[ -e "${IN_BASH}" ] && rm "${IN_BASH}"
		[ -e "${IN_MINI}" ] && rm "${IN_MINI}"
	fi
}

# Initializes the whole testing environment.
# Should be the first test called.
init_world() {
	[ -d "$MAIN_TEST_DIR" ] && rm -rf "$MAIN_TEST_DIR"
	mkdir -p "${MAIN_TEST_DIR}"
	print_header "Testing - mini-shell"
}

# Cleanups the whole testing environment.
# Should be the last test called.
cleanup_world() {
	[ "$DO_CLEANUP" = "yes" ] && rm -rf "$MAIN_TEST_DIR"
}

# ----------------- Test Suite ----------------------------------------------- #

# Specific test example.
execute_cmd() {
	EXEC=$1
	INPUT=$2
	OUTPUT=$3
	[ -z "$OUTPUT" ] && OUTPUT=$LOG_FILE
	mkdir -p "${OUT_DIR}" && cd "${OUT_DIR}" &>"$LOG_FILE" || exit 1
	# shellcheck disable=SC2086
	timeout "$TEST_TIMEOUT" $BUFFERING_WRAPPER $EXEC <"${INPUT}" &>"$OUTPUT"
	# Ocasionally, in a virtualized environment, the diff that compares the
	# target implementation with the reference output starts before the
	# target implementation has finished writing files to disk. Handle this
	# by mandating that all I/O buffers be flushed.
	sync
	cd - &>"$LOG_FILE" || exit 1
}

generate_input() {
	# Generate the PROMPT for BASH.
	sed 's/\(.*\)/printf \"> \"; \1/' "${IN_FILE}" >"${REF_FILE}"
}

# Checks the output of the commands.
test_output() {
	init_test

	generate_input

	# Commands to execute the test.
	execute_cmd "$ref_name" "../${REF_FILE}" "${OUT_FILE}"
	# Move OUT_DIR in order to preserve the pwd output.
	mv "${OUT_DIR}" "${REF_DIR}"
	execute_cmd "$exec_name" "../${IN_FILE}" "${OUT_FILE}"

	# Test output.
	basic_test diff -r -ui -x "$VALGRIND_LOG" "${REF_DIR}" "${OUT_DIR}"

	cleanup_test
}

# Tests common commands.
_test_common() {
	init_test

	# Commands to execute the test.
	execute_cmd "$1" "../${IN_FILE}"
	# Move OUT_DIR in order to preserve the pwd output.
	mv "${OUT_DIR}" "${REF_DIR}"
	execute_cmd "$exec_name" "../${IN_FILE}"

	# Test output.
	basic_test diff -r -ui -x "$VALGRIND_LOG" "${REF_DIR}" "${OUT_DIR}"

	cleanup_test
}

# Default common test.
test_common() {
	_test_common "$ref_name"
}

# Tests common commands using alternate ref.
test_common_alt() {
	if [ "$OS_PLATFORM" == "win" ]; then
		_test_common "$ref_name_alt"
	else
		_test_common "$ref_name"
	fi
}

# Test 18.
test_exec_failed() {
	init_test

	# Commands to execute the.
	execute_cmd "$exec_name" "../${IN_FILE}" "${REF_FILE}"

	# Test output.
	basic_test diff -r -uib "${REF_FILE}" "${OUT_DIR}/${REF_FILE}"

	cleanup_test
}

test_fun_array=(
	test_output "Testing commands without arguments" 3
	test_output "Testing commands with arguments" 2
	test_common "Testing simple redirect operators" 5
	test_common "Testing append redirect operators" 5
	test_common "Testing current directory" 5
	test_common "Testing conditional operators" 5
	test_common "Testing sequential commands" 3
	test_common "Testing environment variables" 5
	test_common "Testing single pipe" 5
	test_common "Testing multiple pipes" 10
	test_common "Testing variables and redirect" 5
	test_common "Testing overwritten variables" 2
	test_common "Testing all operators" 2
	test_common_alt "Testing parallel operator" 10
	test_common_alt "Testing big file" 5
	test_common_alt "Testing sleep command" 7
	test_common_alt "Testing fscanf function" 7
	test_exec_failed "Testing unknown command" 4
)

# ----------------- Run test ------------------------------------------------- #

# First we check if we have everything defined.
check_tests

# Run tests.
run_tests "$@"

exit 0
