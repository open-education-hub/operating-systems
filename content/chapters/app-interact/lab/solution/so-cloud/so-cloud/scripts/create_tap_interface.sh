#!/bin/bash

set -e
set -x

if [ $# -ne 4 ]; then
    echo 'Usage: create_tap_interface.sh interface_name ip mask bridge_name'
    exit 1
fi

if ip tuntap show | grep -q "$1"; then
    :
else
    ip tuntap add "$1" mode tap
    ip link set "$1" master "$4"

    #ip address add "$2"/"$3" dev "$1"
    ip link set "$1" up
fi
