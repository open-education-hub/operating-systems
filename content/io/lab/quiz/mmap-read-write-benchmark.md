# `mmap()` vs `read()` and `write()` Benchmark

## Question Text

According to the times shown by `benchmark_cp.sh`, which of the two implementations is faster?

## Question Answers

- the one using `mmap()`

- the one using `read()` and `write()`

+ they are roughly equivalent

## Feedback

In our case, running the script a few times results in the following running times:

```console
student@os:/.../support/file-mappings$ ./benchmark_cp.sh
make: Nothing to be done for 'all'.
Benchmarking mmap_cp on a 1GB file...

real    0m30,597s
user    0m0,569s
sys	0m2,286s
Benchmarking cp on a 1 GB file...

real    0m36,012s
user    0m0,039s
sys	0m2,469s


student@os:/.../support/file-mappings$ ./benchmark_cp.sh
make: Nothing to be done for 'all'.
Benchmarking mmap_cp on a 1 GB file...

real    0m27,803s
user    0m0,590s
sys	0m2,114s
Benchmarking cp on a 1 GB file...

real    0m35,607s
user    0m0,033s
sys	0m2,564s
```

So it seems that using `mmap()` rather than `read()` and `write()` yields about a 15% increase in performance.
However, you might get different results on your system.
This depends on your storage device (SSD vs HDD) and its specific speed (like its RPM for an HDD).
So the more conservative answer is to say that this depends on external aspects and that, in general, the 2 implementations are more or less equivalent.

If you want to know why there isn't much of a difference between the 2 implementations, check out [this explanation](https://stackoverflow.com/a/27987994).
