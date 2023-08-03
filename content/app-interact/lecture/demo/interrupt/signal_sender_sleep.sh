#!/bin/bash

pid=$(pgrep -f "signal_printer")
if test -z "$pid"; then
    echo "No such process: signal_printer" 1>&2
    exit 1
fi

set -x

# Print 'g'
kill -HUP "$pid"
sleep 1
# Print 'e'
kill -ILL "$pid"
sleep 1
# Print 'r'
kill -TRAP "$pid"
sleep 1
# Print 'o'
kill -ABRT "$pid"
sleep 1
# Print 'n'
kill -BUS "$pid"
sleep 1
# Print 'i'
kill -FPE "$pid"
sleep 1
# Print 'm'
kill -USR1 "$pid"
sleep 1
# Print 'o'
kill -ABRT "$pid"
sleep 1
# Print '\n'
kill -USR2 "$pid"
sleep 1

# End process
kill -INT "$pid"
