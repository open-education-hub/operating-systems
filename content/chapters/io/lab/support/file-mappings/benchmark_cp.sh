#! /bin/bash

make

[ -f large-file.txt ] || make large-file

# Drop all OS caches: buffer cache, dentry cache, inode cache, page cache.
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"

echo "Benchmarking mmap_cp on a 1 GB file..."
# Run the benchmark for `mmap_cp`.
time ./mmap_cp large-file.txt large-file-mmap.txt

# Drop all OS caches: buffer cache, dentry cache, inode cache, page cache.
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"

echo "Benchmarking cp on a 1 GB file..."
# Run the benchmark for `cp`.
time cp large-file.txt large-file-cp.txt
