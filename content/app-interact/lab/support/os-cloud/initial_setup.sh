#!/bin/bash

set -o posix
set -e

# Load the nbd module.
sudo modprobe nbd max_part=16

# Downloading disk templates.
# Original from https://cloud-images.ubuntu.com/releases/22.04/release/ubuntu-22.04-server-cloudimg-amd64.img
DISKS=('https://elf.cs.pub.ro/so/res/mv/ubuntu-22.04-server-cloudimg-amd64.qcow2' 'ubuntu_22.04')

len=${#DISKS[@]}
for ((i = 0; i < len/2; i++)); do
    url=${DISKS[2*i]}
    name=${DISKS[2*i+1]}
    wget --no-check-certificate "$url" -O "./disk-templates/$name/$name.qcow2"
done

# Pull docker images
docker pull mariadb:10.7

