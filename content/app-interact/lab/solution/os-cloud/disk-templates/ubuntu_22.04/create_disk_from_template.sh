#!/bin/bash

set -o posix
set -e

if [ $# -ne 3 ]; then
    echo 'Usage: create_disk_from_template.sh source_disk.qcow2 destination_disk.qcow2 size'
    exit 1
fi

source_disk="$1"
destination_disk="$2"
size="$3"

disk_dir=$(dirname "$destination_disk")

mkdir -p "$disk_dir"

cp "$source_disk" "$destination_disk"

# Resize the disk to the desired size.
qemu-img resize -f qcow2 "$destination_disk" "$size"
