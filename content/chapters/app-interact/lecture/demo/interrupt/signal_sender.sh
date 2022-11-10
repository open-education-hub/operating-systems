#!/bin/bash

pid=$(pgrep -f "signal_printer")
if test -z "$pid"; then
    echo "No such process: signal_printer" 1>&2
    exit 1
fi

set -x
# Print 'g'
kill -HUP "$pid"
# Print 'e'
kill -ILL "$pid"
# Print 'r'
kill -TRAP "$pid"
# Print 'o'
kill -ABRT "$pid"
# Print 'n'
kill -BUS "$pid"
# Print 'i'
kill -FPE "$pid"
# Print 'm'
kill -USR1 "$pid"
# Print 'o'
kill -ABRT "$pid"
# Print '\n'
kill -USR2 "$pid"

sleep 3

# End process
kill -INT "$pid"
