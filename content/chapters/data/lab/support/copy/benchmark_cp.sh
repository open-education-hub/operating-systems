#! /bin/bash

# [WARNING]
# This script should be run from local environment
# The Docker container does not have permission to write to `/proc/sys/vm/_drop_caches`

# Drop all OS caches: buffer cache, dentry cache, inode cache, page cache.
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"

echo "Benchmarking mmap_copy on in.dat"
# Run the benchmark for `mmap_copy`.
./mmap_copy
echo ""

# Drop all OS caches: buffer cache, dentry cache, inode cache, page cache.
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"

echo "Benchmarking read_write_copy on in.dat"
# Run the benchmark for `read_write_copy`.
./read_write_copy
echo ""
