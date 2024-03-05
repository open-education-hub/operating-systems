#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

(
./test_string

./test_io_file_create.sh
./test_io
./test_io_file_delete.sh
./test_puts.sh

./test_open_close.sh
./test_ftruncate.sh
./test_truncate.sh
./test_fstat.sh
./test_stat.sh

./test_sleep.sh
./test_nanosleep.sh

./test_memory
./test_malloc.sh
./test_multiple_malloc.sh
./test_malloc_free.sh
./test_multiple_malloc_free.sh
./test_malloc_free_sequence.sh
./test_malloc_perm_ok.sh
./test_malloc_perm_notok.sh
./test_mmap.sh
./test_mmap_munmap.sh
./test_mmap_perm_ok.sh
./test_mmap_perm_notok.sh
./test_mmap_perm_none.sh
) | tee results.txt

total=$(grep '\( passed \| failed \)' results.txt | rev | cut -d ' ' -f 1 | rev | paste -s -d'+' | bc)
total_grade=$( (echo "scale=0"; echo "$total / 10") | bc )
echo ""
echo -n "Total:                           "
echo -n "                                "
LC_ALL=C printf "%3d/100\n" "$total_grade"

rm results.txt
