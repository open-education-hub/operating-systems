#!/bin/bash

set -e

if [ $# -ne 3 ]; then
    echo 'Usage: create_bridge.sh bridge_name bridge_ip bridge_mask'
    exit 1
fi

ip link add "$1" type bridge
ip address add "$2"/"$3" dev "$1"
ip link set "$1" up
