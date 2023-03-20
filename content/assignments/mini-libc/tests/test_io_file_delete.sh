#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

# delete RDONLY file
rm -f ./file_RDONLY

# delete RW file
rm -f ./file_RW

# delete directory
rmdir ./dir

# delete empty file
rm -f ./file_EMPTY

# delete created file
rm -f ./file_CREATE
