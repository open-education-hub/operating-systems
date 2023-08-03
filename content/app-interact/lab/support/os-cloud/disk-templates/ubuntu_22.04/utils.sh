#!/bin/bash

nbd_connect_qcow2()
{
    local src="$1"

    local nbd_idx=0

    while [ $nbd_idx -lt 16 ]; do
	if qemu-nbd -c /dev/nbd${nbd_idx} "$src" &> /dev/null; then
	    partprobe

	    # Wait for partitions to appear
	    for _ in $(seq 1 60); do
		if compgen -G "/dev/nbd${nbd_idx}p*" > /dev/null; then
		    sleep 1
		    echo "/dev/nbd${nbd_idx}"
		    return
		fi
		sleep 1
	    done

	    break
	fi

	nbd_idx=$((nbd_idx + 1))
    done

    false
}
