#!/bin/bash

set -o posix
set -e

# shellcheck source=content/chapters/app-interact/lab/solution/os-cloud/disk-templates/ubuntu_22.04/utils.sh
source "$(dirname -- "${BASH_SOURCE[0]}")/utils.sh"

if [ $EUID -ne 0 ]; then
    echo 'This script must run as root'
    exit 1
fi

if [ ! -e /dev/nbd0 ]; then
    echo 'nbd kernel module not present'
    exit 1
fi

if [ $# -ne 1 ]; then
    echo 'Usage: setup_root_password.sh disk.qcow2'
    exit 1
fi

source_disk="$1"

disk_dir=$(dirname "$source_disk")
disk_mnt_dir="$disk_dir/mnt"

mkdir -p "$disk_mnt_dir"

# Mount qcow2.
nbd_dev=$(nbd_connect_qcow2 "$source_disk")
mount "${nbd_dev}p1" "$disk_mnt_dir"
# -----------

cp files/99-os-cloud-welcome "$disk_mnt_dir/etc/update-motd.d"

# Unmount qcow2.
umount -l "$disk_mnt_dir"
qemu-nbd -d "$nbd_dev"
# ------------
