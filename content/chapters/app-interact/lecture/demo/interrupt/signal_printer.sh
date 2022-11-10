#!/bin/bash

DEBUG=0

trap 'echo -n "g"' SIGHUP
trap 'echo -n "e"' SIGILL
trap 'echo -n "r"' SIGTRAP
trap 'echo -n "o"' SIGABRT
trap 'echo -n "n"' SIGBUS
trap 'echo -n "i"' SIGFPE
trap 'echo -n "m"' SIGUSR1
trap 'echo ""' SIGUSR2

while true; do
    read -r
    test "$DEBUG" -eq 1 && echo "signal received"
done
