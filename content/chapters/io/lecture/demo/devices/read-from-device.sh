#!/bin/bash

if [[ $# != 1 ]]; then
    echo "usage: $0 <device>"
    exit 0
fi

BS=1
COUNT=100
DEV=$1

echo "Read $((COUNT * BS)) bytes from $DEV:"

dd if="$DEV" bs="$BS" count="$COUNT" status=none | hexdump
