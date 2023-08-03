#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

# create RDONLY file
touch ./file_RDONLY
chmod ugo+r-xw ./file_RDONLY

# create RW file
touch ./file_RW
chmod ugo+rw-x ./file_RW

# create directory
mkdir ./dir

# create empty file
truncate -s 0 ./file_EMPTY
