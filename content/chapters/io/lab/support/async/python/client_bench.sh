#!/bin/bash

NUM_CLIENTS=8

for _ in $(seq 1 $NUM_CLIENTS); do
    ./client.py localhost 2999 30 &
done
wait
