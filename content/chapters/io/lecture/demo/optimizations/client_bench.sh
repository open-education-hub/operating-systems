#!/bin/bash

if [[ $# != 1 ]]; then
    echo "usage: $0 <port>"
    exit 1
fi

NUM_CLIENTS=8
PORT=$1

for i in $(seq 1 $NUM_CLIENTS); do
    ./client.py localhost "$1" 30 &
done
wait
