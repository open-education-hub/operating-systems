#!/bin/sh
# SPDX-License-Identifier: BSD-3-Clause

PATH_TO_VM_IMAGE="$1"
CORES="$2"
MEMORY="$3"
INTERFACE="$4"

qemu-system-x86_64 -hda "$PATH_TO_VM_IMAGE" \
-boot d -m "$MEMORY"G -usb -machine q35 -cpu max -smp cores="$CORES",threads=1,sockets=1 \
-nic vmnet-bridged,ifname="$INTERFACE" &
