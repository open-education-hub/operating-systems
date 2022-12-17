#!/bin/bash

nbd_connect_qcow2()
{
    local src="$1"

    local nbd_idx=0

    while [ $nbd_idx -lt 16 ]; do
	if qemu-nbd -c /dev/nbd${nbd_idx} "$src" &> /dev/null; then
	    partprobe
	    echo "/dev/nbd${nbd_idx}"
	    return
	fi

	nbd_idx=$((nbd_idx + 1))
    done

    false
}
