#!/bin/bash

pid=$(pgrep -f "rt_signal_printer")
if test -z "$pid"; then
    echo "No such process: rt_signal_printer" 1>&2
    exit 1
fi

set -x
# Print 'g'
kill -RTMIN "$pid"
# Print 'e'
kill -RTMIN+1 "$pid"
# Print 'r'
kill -RTMIN+2 "$pid"
# Print 'o'
kill -RTMIN+3 "$pid"
# Print 'n'
kill -RTMIN+4 "$pid"
# Print 'i'
kill -RTMIN+5 "$pid"
# Print 'm'
kill -RTMIN+6 "$pid"
# Print 'o'
kill -RTMIN+3 "$pid"
# Print '\n'
kill -RTMIN+7 "$pid"

sleep 3

# End process
kill -INT "$pid"
