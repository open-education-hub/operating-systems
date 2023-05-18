#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

exec_name="./aws"
exec_pid=-1
aws_listen_port=8888
static_folder="./static/"
dynamic_folder="./dynamic/"

LOG_FILE=test.log
WGET_LOG=wget.log

# Enable/disable cleanup (yes/no)
DO_CLEANUP=yes

max_points=90

# Enable/disable exiting when program fails (1/0)
EXIT_IF_FAIL=0

# Enable/disable debug (1/0)
DEBUG_=0

DEBUG()
{
    if test "x$DEBUG_" = "x1"; then
        "$@" 1>&2
    fi
}

MEMCHECK_ERR_CODE=123
MEMCHECK="valgrind --leak-check=full \
    --show-reachable=yes \
    --vex-iropt-register-updates=allregs-at-mem-access \
    --show-leak-kinds=all \
    --error-exitcode=$MEMCHECK_ERR_CODE \
    $MEMCHECK_EXTRA \
    --log-file=_log "

memory_test()
{
    DEBUG echo "MEM TEST"

    if [ -z "$mem_points" ] || [ "$mem_points" = "0" ]; then
        return
    fi

    res=$1
    memcheck_description="$description - memcheck"
    printf "%02d) %s" "$test_index" "$memcheck_description"

    for ((i = 0; i < 67 - ${#memcheck_description}; i++)); do
        printf "."
    done

    if test "$res" -ne "$MEMCHECK_ERR_CODE"; then
        test_do_pass "$mem_points"
    else
        test_do_fail "$mem_points"
    fi
}


print_header()
{
    header="${1}"
    header_len=${#header}

    printf "\n"
    if [ "$header_len" -lt 82 ]; then
        padding=$(((82 - header_len) / 2))
        for ((i = 0; i < padding; i++)); do
            printf " "
        done
    fi
    printf "= %s =\n\n" "${header}"
}

test_do_fail()
{
    points=$1
    printf "failed  [ 0/%02d]\n" $max_points
    if test "x$EXIT_IF_FAIL" = "x1"; then
        exit 1
    fi
}

test_do_pass()
{
    points=$1
    printf "passed  [%02d/%02d]\n" "$points" "$max_points"
}

basic_test()
{
    printf "%02d) %s" "$test_index" "$description"

    for ((i = 0; i < 67 - ${#description}; ++i)); do
        printf "."
    done

    "$@" > /dev/null 2>&1
    if test $? -eq 0; then
        test_do_pass "$points"
    else
        test_do_fail "$points"
    fi
}

# ---------------------------------------------------------------------------- #

# ----------------- Init and cleanup tests ----------------------------------- #

# Initializes a test
init_test()
{
    libpath="$(readlink -f _test/sockop_preload.so)"

    if test ! -f "$libpath"; then
        echo "Cannot find $libpath"
        exit 1
    fi

    if [ "$mem_points" != 0 ]; then
        MEMCHECK_TEST=$MEMCHECK
    else
        MEMCHECK_TEST=
    fi

    LD_PRELOAD="$libpath" $MEMCHECK_TEST $exec_name &>> "$LOG_FILE" &
    if test $? -eq 0; then
        exec_pid=$!
    fi

    sleep 2
}

# Cleanups a test
cleanup_test()
{
    kill -9 "$exec_pid" &>> $LOG_FILE

    if [ "$DO_CLEANUP" = "yes" ]; then
        rm -rf "$WGET_LOG" &>> $LOG_FILE
    fi

    wait "$exec_pid" > /dev/null 2>&1
    memory_test $?
}

# Initializes the whole testing environment
# Should be the first test called
init_world()
{
    [ -d "$static_folder" ] && rm -rf "$static_folder" &>> "$LOG_FILE"
    [ -d "$dynamic_folder" ] && rm -rf "$dynamic_folder" &>> "$LOG_FILE"
    mkdir "$static_folder" &>> "$LOG_FILE"
    mkdir "$dynamic_folder" &>> "$LOG_FILE"

    print_header "Testing - Asynchronous Web Server"

    for i in $(seq -f "%02g" 0 49); do
        dd if=/dev/urandom of="$static_folder"/small"$i".dat \
            bs=2K count=1 &>> "$LOG_FILE"
        dd if=/dev/urandom of="$static_folder"/large"$i".dat \
            bs=2M count=1 &>> "$LOG_FILE"
        ln -sf ../"$static_folder"/small"$i".dat "$dynamic_folder"/small"$i".dat
        ln -sf ../"$static_folder"/large"$i".dat "$dynamic_folder"/large"$i".dat
    done
}

# Cleanups the whole testing environment
# Should be the last test called
cleanup_world()
{
    if [ "$DO_CLEANUP" = "yes" ]; then
        rm -fr "$static_folder" &>> "$LOG_FILE"
        rm -fr "$dynamic_folder" &>> "$LOG_FILE"
        rm -fr "$LOG_FILE"
    fi
}

# ---------------------------------------------------------------------------- #

# ----------------- Test Suite ----------------------------------------------- #

test_executable_exists()
{
    init_test

    basic_test test -e "$exec_name"

    cleanup_test
}

test_executable_runs()
{
    init_test

    basic_test ps -C aws

    cleanup_test
}

# Use lsof to see whether server is listening on proper port
test_is_listening()
{
    init_test

    lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | grep TCP | \
        grep LISTEN > /dev/null 2>&1
    basic_test test $? -eq 0

    cleanup_test
}

test_is_listening_on_port()
{
    init_test

    lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $9;}' | grep TCP | \
        grep "$aws_listen_port" > /dev/null 2>&1
    basic_test test $? -eq 0

    cleanup_test
}

# Use netcat for connecting to server
test_accepts_connections()
{
    init_test

    nc localhost "$aws_listen_port" 0<&- &
    nc_pid=$!
    sleep 1

    lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | grep TCP | \
        grep ESTABLISHED > /dev/null 2>&1
    basic_test test $? -eq 0

    kill -9 "$nc_pid" > /dev/null 2>&1
    wait "$nc_pid" > /dev/null 2>&1

    cleanup_test
}

test_accepts_multiple_connections()
{
    init_test

    nc localhost "$aws_listen_port" 0<&- &
    nc_pid1=$!
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid2=$!
    sleep 1

    n_conns=$(lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | \
        grep TCP | grep -c ESTABLISHED 2> /dev/null)
    DEBUG echo "n_conns: $n_conns"
    basic_test test "$n_conns" -eq 2

    kill -9 "$nc_pid1" "$nc_pid2" > /dev/null 2>&1
    wait "$nc_pid1" "$nc_pid2" > /dev/null 2>&1

    cleanup_test
}

# Use nm to list undefined symbols in executable file
test_uses_epoll()
{
    init_test

    nm -u "$exec_name" | grep epoll > /dev/null 2>&1
    basic_test test $? -eq 0

    cleanup_test
}

test_disconnect()
{
    init_test

    nc localhost "$aws_listen_port" 0<&- &
    nc_pid=$!
    sleep 1

    n_conns=$(lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | \
        grep TCP | grep -c ESTABLISHED 2> /dev/null)

    kill -9 "$nc_pid" > /dev/null 2>&1
    wait "$nc_pid" > /dev/null 2>&1

    lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | grep TCP | \
        grep ESTABLISHED > /dev/null 2>&1
    basic_test test "$n_conns" -eq 1 -a $? -ne 0

    cleanup_test
}

test_multiple_disconnect()
{
    init_test

    nc localhost "$aws_listen_port" 0<&- &
    nc_pid1=$!
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid2=$!
    sleep 1

    n_conns=$(lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | \
        grep TCP | grep -c ESTABLISHED 2> /dev/null)

    kill -9 "$nc_pid1" "$nc_pid2" > /dev/null 2>&1
    wait "$nc_pid1" "$nc_pid2" > /dev/null 2>&1

    lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | grep TCP | \
        grep ESTABLISHED > /dev/null 2>&1
    basic_test test "$n_conns" -eq 2 -a $? -ne 0

    cleanup_test
}

test_connect_disconnect_connect()
{
    init_test

    nc localhost "$aws_listen_port" 0<&- &
    nc_pid=$!
    kill -9 "$nc_pid" > /dev/null 2>&1
    wait "$nc_pid" > /dev/null 2>&1
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid=$!
    sleep 1

    lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | grep TCP | \
        grep ESTABLISHED > /dev/null 2>&1
    basic_test test $? -eq 0

    kill -9 "$nc_pid" > /dev/null 2>&1
    wait "$nc_pid" > /dev/null 2>&1

    cleanup_test
}

test_multiple_connect_disconnect_connect()
{
    init_test

    nc localhost "$aws_listen_port" 0<&- &
    nc_pid1=$!
    kill -9 "$nc_pid1" > /dev/null 2>&1
    wait "$nc_pid1" > /dev/null 2>&1
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid1=$!
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid2=$!
    kill -9 "$nc_pid2" > /dev/null 2>&1
    wait "$nc_pid2" > /dev/null 2>&1
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid2=$!
    sleep 1

    n_conns=$(lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | \
        grep TCP | grep -c ESTABLISHED 2> /dev/null)
    DEBUG echo "n_conns: $n_conns"
    basic_test test "$n_conns" -eq 2

    kill -9 "$nc_pid1" "$nc_pid2" > /dev/null 2>&1
    wait "$nc_pid1" "$nc_pid2" > /dev/null 2>&1

    cleanup_test
}

test_unordered_connect_disconnect_connect()
{
    init_test

    nc localhost "$aws_listen_port" 0<&- &
    nc_pid1=$!
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid2=$!
    kill -9 "$nc_pid1" "$nc_pid2" > /dev/null 2>&1
    wait "$nc_pid1" "$nc_pid2" > /dev/null 2>&1
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid1=$!
    nc localhost "$aws_listen_port" 0<&- &
    nc_pid2=$!
    sleep 1

    n_conns=$(lsof -p "$exec_pid" | awk -F '[ \t]+' '{print $8, $10;}' | \
        grep TCP | grep -c ESTABLISHED 2> /dev/null)
    DEBUG echo "n_conns: $n_conns"
    basic_test test "$n_conns" -eq 2

    kill -9 "$nc_pid1" "$nc_pid2" > /dev/null 2>&1
    wait "$nc_pid1" "$nc_pid2" > /dev/null 2>&1

    cleanup_test
}

test_replies_http_request()
{
    init_test

    echo -ne "GET /$(basename $static_folder)/small00.dat HTTP/1.0\r\n\r\n" | \
        nc -q 1 localhost "$aws_listen_port" > small00.dat 2> /dev/null

    head -1 small00.dat | grep '^HTTP/' > /dev/null 2>&1
    basic_test test $? -eq 0

    rm small00.dat
    cleanup_test
}

test_replies_http_request_1()
{
    init_test

    echo -ne "GET /$(basename $static_folder)/small00.dat HTTP/1.1\r\n\r\n" | \
        nc -q 1 localhost "$aws_listen_port" > small00.dat 2> /dev/null

    head -1 small00.dat | grep '^HTTP/' > /dev/null 2>&1
    basic_test test $? -eq 0

    rm small00.dat
    cleanup_test
}

test_uses_sendfile()
{
    init_test

    nm -u "$exec_name" | grep sendfile > /dev/null 2>&1
    basic_test test $? -eq 0

    cleanup_test
}

test_get_small_file_wget()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $static_folder)/small00.dat" \
        -o "$WGET_LOG" -O small00.dat
    code1=$?

    [ -s small00.dat ]
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm small00.dat
    cleanup_test
}

test_get_small_file_wget_cmp()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $static_folder)/small00.dat" \
        -o "$WGET_LOG" -O small00.dat

    cmp small00.dat $static_folder/small00.dat > /dev/null 2>&1
    basic_test test $? -eq 0

    rm small00.dat
    cleanup_test
}

test_get_large_file_wget()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $static_folder)/large00.dat" \
        -o "$WGET_LOG" -O large00.dat
    code1=$?

    [ -s large00.dat ]
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm large00.dat
    cleanup_test
}

test_get_large_file_wget_cmp()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $static_folder)/large00.dat" \
        -o "$WGET_LOG" -O large00.dat

    cmp large00.dat $static_folder/large00.dat > /dev/null 2>&1
    basic_test test $? -eq 0

    rm large00.dat
    cleanup_test
}

test_get_bad_file_404()
{
    init_test

    echo -ne "GET /$(basename $static_folder)/abcdef.dat HTTP/1.0\r\n\r\n" | \
        nc -q 1 localhost "$aws_listen_port" > abcdef.dat 2> /dev/null

    head -1 abcdef.dat | grep '^HTTP/' | grep '404' > /dev/null 2>&1
    basic_test test $? -eq 0

    rm abcdef.dat
    cleanup_test
}

# Use non-static and non-dynamic file path
test_bad_path_404()
{
    init_test

    echo -ne "GET /xyzt/abcdef.dat HTTP/1.0\r\n\r\n" | \
        nc -q 1 localhost "$aws_listen_port" > abcdef.dat 2> /dev/null

    head -1 abcdef.dat | grep '^HTTP/' | grep '404' > /dev/null 2>&1
    basic_test test $? -eq 0

    rm abcdef.dat
    cleanup_test
}

test_get_one_file_then_another()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $static_folder)/large00.dat" \
        -o /dev/null -O large00.dat
    wget -t 1 "http://localhost:8888/$(basename $static_folder)/large01.dat" \
        -o /dev/null -O large01.dat

    cmp large00.dat $static_folder/large00.dat > /dev/null 2>&1
    code1=$?
    cmp large01.dat $static_folder/large01.dat > /dev/null 2>&1
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm large00.dat large01.dat
    cleanup_test
}

test_get_two_simultaneous_files()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $static_folder)/large00.dat" \
        -o /dev/null -O large00.dat &
    pid1=$!
    wget -t 1 "http://localhost:8888/$(basename $static_folder)/large01.dat" \
        -o /dev/null -O large01.dat &
    pid2=$!
    wait "$pid1" $pid2 > /dev/null 2>&1

    cmp large00.dat $static_folder/large00.dat > /dev/null 2>&1
    code1=$?
    cmp large01.dat $static_folder/large01.dat > /dev/null 2>&1
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm large00.dat large01.dat
    cleanup_test
}

test_get_multiple_simultaneous_files()
{
    init_test

    ret_val=0
    declare -a pids

    for i in $(seq 0 49); do
        filename=large$(printf "%02g" "$i").dat
        wget -t 1 "http://localhost:8888/$(basename $static_folder)/$filename" \
            -o /dev/null -O "$filename" &
        pids[$i]=$!
    done
    for i in $(seq 0 49); do
        wait ${pids[$i]} > /dev/null 2>&1
    done

    for i in $(seq 0 49); do
        filename=large$(printf "%02g" "$i").dat
        if ! cmp "$static_folder/$filename" "$filename" > /dev/null 2>&1; then
            ret_val=1
            break
        fi
    done
    basic_test test "$ret_val" -eq 0

    for i in $(seq 0 49); do
        filename=large$(printf "%02g" "$i").dat
        rm "$filename"
    done
    cleanup_test
}

test_uses_io_submit()
{
    init_test

    nm -u "$exec_name" | grep io_submit > /dev/null 2>&1
    basic_test test $? -eq 0

    cleanup_test
}

test_get_small_dyn_file_wget()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/small00.dat" \
        -o "$WGET_LOG" -O small00.dat
    code1=$?

    [ -s small00.dat ]
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm small00.dat
    cleanup_test
}

test_get_small_dyn_file_wget_cmp()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/small00.dat" \
        -o "$WGET_LOG" -O small00.dat

    cmp small00.dat $dynamic_folder/small00.dat > /dev/null 2>&1
    basic_test test $? -eq 0

    rm small00.dat
    cleanup_test
}

test_get_large_dyn_file_wget()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/large00.dat" \
        -o "$WGET_LOG" -O large00.dat
    code1=$?

    [ -s large00.dat ]
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm large00.dat
    cleanup_test
}

test_get_large_dyn_file_wget_cmp()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/large00.dat" \
        -o "$WGET_LOG" -O large00.dat

    cmp large00.dat $dynamic_folder/large00.dat > /dev/null 2>&1
    basic_test test $? -eq 0

    rm large00.dat
    cleanup_test
}

test_get_bad_dyn_file_404()
{
    init_test

    echo -ne "GET /$(basename $dynamic_folder)/abcdef.dat HTTP/1.0\r\n\r\n" | \
        nc -q 1 localhost "$aws_listen_port" > abcdef.dat 2> /dev/null

    head -1 abcdef.dat | grep '^HTTP/' | grep '404' > /dev/null 2>&1
    basic_test test $? -eq 0

    rm abcdef.dat
    cleanup_test
}

test_get_one_dyn_file_then_another()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/large00.dat" \
        -o /dev/null -O large00.dat
    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/large01.dat" \
        -o /dev/null -O large01.dat

    cmp large00.dat $dynamic_folder/large00.dat > /dev/null 2>&1
    code1=$?
    cmp large01.dat $dynamic_folder/large01.dat > /dev/null 2>&1
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm large00.dat large01.dat
    cleanup_test
}

test_get_two_simultaneous_dyn_files()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/large00.dat" \
        -o /dev/null -O large00.dat &
    pid1=$!
    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/large01.dat" \
        -o /dev/null -O large01.dat &
    pid2=$!
    wait "$pid1" $pid2 > /dev/null 2>&1

    cmp large00.dat $dynamic_folder/large00.dat > /dev/null 2>&1
    code1=$?
    cmp large01.dat $dynamic_folder/large01.dat > /dev/null 2>&1
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm large00.dat large01.dat
    cleanup_test
}

test_get_multiple_simultaneous_dyn_files()
{
    init_test

    ret_val=0
    declare -a pids

    for i in $(seq 0 49); do
        filename=large$(printf "%02g" "$i").dat
        wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/$filename" \
            -o /dev/null -O "$filename" &
        pids[$i]=$!
    done
    for i in $(seq 0 49); do
        wait ${pids[$i]} > /dev/null 2>&1
    done

    for i in $(seq 0 49); do
        filename=large$(printf "%02g" "$i").dat
        if ! cmp "$dynamic_folder/$filename" "$filename" > /dev/null 2>&1; then
            ret_val=1
            break
        fi
    done
    basic_test test "$ret_val" -eq 0

    for i in $(seq 0 49); do
        filename=large$(printf "%02g" "$i").dat
        rm "$filename"
    done
    cleanup_test
}

test_get_two_simultaneous_stat_dyn_files()
{
    init_test

    wget -t 1 "http://localhost:8888/$(basename $static_folder)/large00.dat" \
        -o /dev/null -O large00.dat &
    pid1=$!
    wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/large01.dat" \
        -o /dev/null -O large01.dat &
    pid2=$!
    wait "$pid1" $pid2 > /dev/null 2>&1

    cmp large00.dat $static_folder/large00.dat > /dev/null 2>&1
    code1=$?
    cmp large01.dat $dynamic_folder/large01.dat > /dev/null 2>&1
    code2=$?
    basic_test test "$code1" -eq 0 -a "$code2" -eq 0

    rm large00.dat large01.dat
    cleanup_test
}

test_get_multiple_simultaneous_stat_dyn_files()
{
    init_test

    ret_val=0
    declare -a pids

    for i in $(seq 0 24); do
        filename=large$(printf "%02g" "$i").dat
        wget -t 1 "http://localhost:8888/$(basename $static_folder)/$filename" \
            -o /dev/null -O "$filename" &
        pids[$i]=$!
    done
    for i in $(seq 25 49); do
        filename=large$(printf "%02g" "$i").dat
        wget -t 1 "http://localhost:8888/$(basename $dynamic_folder)/$filename" \
            -o /dev/null -O "$filename" &
        pids[$i]=$!
    done
    for i in $(seq 0 49); do
        wait ${pids[$i]} > /dev/null 2>&1
    done

    for i in $(seq 0 24); do
        filename=large$(printf "%02g" "$i").dat
        if ! cmp "$static_folder/$filename" "$filename" > /dev/null 2>&1; then
            ret_val=1
            break
        fi
    done
    for i in $(seq 25 49); do
        filename=large$(printf "%02g" "$i").dat
        if ! cmp "$dynamic_folder/$filename" "$filename" > /dev/null 2>&1; then
            ret_val=1
            break
        fi
    done
    basic_test test "$ret_val" -eq 0

    for i in $(seq 0 49); do
        filename=large$(printf "%02g" "$i").dat
        rm "$filename"
    done
    cleanup_test
}

# Specifies the tests, commands and points
test_fun_array=( \
    test_executable_exists "Test executable exists" 1 0
test_executable_runs "Test executable runs" 1 0
test_is_listening "Test listening" 1 0
test_is_listening_on_port "Test listening on port" 1 0
test_accepts_connections "Test accepts connections" 1 0
test_accepts_multiple_connections "Test accepts multiple connections" 1 0
test_uses_epoll "Test epoll usage" 1 0
test_disconnect "Test disconnect" 1 0
test_multiple_disconnect "Test multiple disconnect" 1 0
test_connect_disconnect_connect "Test connect disconnect connect" 1 0
test_multiple_connect_disconnect_connect "Test multiple connect disconnect connect" 1 0
test_unordered_connect_disconnect_connect "Test unordered connect disconnect connect" 1 0
test_replies_http_request "Test replies http request" 2 1
test_replies_http_request_1 "Test second replies http request" 1 0
test_uses_sendfile "Test sendfile usage" 2 0
test_get_small_file_wget "Test small static file wget" 2 0
test_get_small_file_wget_cmp "Test small static file wget cmp" 4 1
test_get_large_file_wget "Test large static file wget" 2 0
test_get_large_file_wget_cmp "Test large static file wget cmp" 4 1
test_get_bad_file_404 "Test bad static file 404" 2 0
test_bad_path_404 "Test bad path 404" 2 0
test_get_one_file_then_another "Test get one static file then another" 2 1
test_get_two_simultaneous_files "Test get two simultaneous static files" 3 1
test_get_multiple_simultaneous_files "Test get multiple simultaneous static files" 4 1
test_uses_io_submit "Test io submit uses" 2 0
test_get_small_dyn_file_wget "Test small dynamic file wget" 2 0
test_get_small_dyn_file_wget_cmp "Test small dynamic file wget cmp" 4 1
test_get_large_dyn_file_wget "Test large dynamic file wget" 2 0
test_get_large_dyn_file_wget_cmp "Test large dynamic file wget cmp" 4 1
test_get_bad_dyn_file_404 "Test bad dynamic file 404" 2 0
test_get_one_dyn_file_then_another "Test get one dynamic file then another" 3 1
test_get_two_simultaneous_dyn_files "Test get two simultaneous dynamic files" 4 1
test_get_multiple_simultaneous_dyn_files "Test get multiple simultaneous dynamic files" 5 1
test_get_two_simultaneous_stat_dyn_files "Test get two simultaneous static and dynamic files" 3 1
test_get_multiple_simultaneous_stat_dyn_files "Test get multiple simultaneous static and dynamic files" 4 1
)

# ---------------------------------------------------------------------------- #

# ----------------- Run test ------------------------------------------------- #

if test $# -ne 1; then
    echo "Usage: $0 <test_number> | init | cleanup" 1>&2
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

arr_index=$(((test_index - 1) * 4))
last_test=$((${#test_fun_array[@]} / 4))
description=${test_fun_array[$((arr_index + 1))]}
points=${test_fun_array[$((arr_index + 2))]}
mem_points=${test_fun_array[$((arr_index + 3))]}

if test "$test_index" -lt 1 -o "$test_index" -gt "$last_test"; then
    echo "Error: Test index is out range (1 <= test_index <= $last_test)." 1>&2
    exit 1
fi

# Run proper function
${test_fun_array[$((arr_index))]}

exit 0
