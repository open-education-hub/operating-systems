# Copy a File with `mmap()`

Navigate to `file-descriptors/drills/tasks/mmap_cp` and run `make` to generate `support`.
As you know `mmap()` can map files in memory, perform operations on them, and then write them back to the disk.
Let's check how well it performs by comparing it to the `cp` command.
The benchmarking is automated by `benchmark_cp.sh` so focus on completing `mmap_cp.c` for now.

[Quiz: Checkout what syscalls `cp` uses](../../questions/syscalls-cp.md)

1. Inside the `tests/` directory, you will need to run `checker.sh`. The output for a successful implementation should look like this:

```bash
./checker.sh
make: Nothing to be done for 'all'.

Test PASSED (File copies are identical)
```
If possible, try to manually test your implementation. Use `./checker.sh` only when you are sure of your result.

1. Open `mmap_cp.c` and complete the TODOs to map the files in memory and copy the contents.
   Do not forget to clean up by unmapping and closing the files.

   To test, run `make test-file` to generate a 1MB file with random data, and then run `mmap_cp test-file output.txt`.
   Ensure they have the same content with a simple `diff`: `diff test-file.txt output.txt`.

1. Compare your implementation to the `cp` command.
   Run `make large-file` to generate a 1GB file with random data, and then run `./benchmark_cp.sh`.

   [Quiz: Debunk why `cp` is winning](../../questions/mmap-read-write-benchmark.md)

   If you want a more generic answer, checkout this [guide on `mmap` vs `read()-write()`](../../../guides/file-mappings/README.md).

1. This demo would not be complete without some live analysis.
   Uncomment the calls to `wait_for_input()` and rerun the program.
   In another terminal, run `cat /proc/$(pidof mmap_cp)/maps` to see mapped files, and `ps -o pid,vsz,rss <PID>` to see how demand paging happens.
