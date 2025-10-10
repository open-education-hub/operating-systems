# Buffering

Navigate to `chapters/io/drills/tasks/buffering/support` and run `make`.
We'll checkout how effective buffering is in `libc` and then we'll do it ourselves.

1. First, let's checkout how relevant buffering is.
   We'll see how well reading and writing **one byte at a time** performs with `no_buffering` and with `libc` buffering.
   Use `benchmark_buffering.sh` script to compare `no_buffering` and `libc_buffering` implementations:

   ```bash
   student@os:/.../buffering/support$ ./benchmark_buffering.sh
   ======== Testing no_buffering ========
   Testing no_buffering read...
   Read 1048576 bytes from test-file.txt in 717 ms
   Testing no_buffering write...
   Wrote 1048576 bytes to test-file.txt in 19632 ms
   ======== Testing libc_buffering ========
   Testing libc_buffering read...
   Read 1048576 bytes from test-file.txt in 14 ms
   Testing libc_buffering write...
   Wrote 1048576 bytes to test-file.txt in 38 ms
   ```
   If possible, try to manually test your implementation. Use `./checker.sh` only when you are sure of your result.

   Buffering achieves dramatic performance gains, reducing read times by **98%** and write times by **99.8%** in this example!
   This demonstrates the power of buffering, even though it’s an extreme case.

1. Complete the TODOs in `diy_buffering.c` to replicate the functionality of `fread()` and `fwrite()`.
   The `fread()` function is already complete, so you can use it as a reference for implementing `fwrite()`.

   After implementing `diy_fwrite()`, run `benchmark_buffering.sh` to see if your DIY buffering implementation outperforms `no_buffering`.
   Check how close you come to the efficiency of `libc`.

Keep in mind that I/O buffering is a core optimization in standard libraries like libc, is so effective that the kernel itself uses it.
The kernel’s **double buffering** strategy reads more than requested, storing extra data in a buffer for future use.
In the next section on [Zero-Copy Techniques](../../../../optimizations/reading/zero-copy.md), we’ll look at how to leverage this to further optimize network requests.

> **Note**: `benchmark_buffering.sh` also includes `echo 3 > /proc/sys/vm/drop_caches` to clear caches before benchmarking, ensuring consistent results.
  For a deeper dive into cache behavior, check out [this section in the Arena](../../arena/reading/arena.md#to-drop-or-not-to-drop).
