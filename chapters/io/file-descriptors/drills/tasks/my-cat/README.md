# My `cat`

Navigate to `chapters/io/file-descriptors/drills/tasks/my-cat/support/src` and checkout `my_cat.c`.
We propose to implement the Linux command `cat` that reads one or more files, **concatenates** them (hence the name `cat`), and prints them to standard output.

1. Inside the `tests/` directory, you will need to run `checker.sh`. The output for a successful implementation should look like this:

```bash
./checker.sh
make: Nothing to be done for 'all'.

Test 1: Comparing single file output..........................PASSED (+30 points)
Test 2: Comparing multiple files output.......................PASSED (+30 points)
Test 3: Testing empty file....................................PASSED (+30 points)
----------------------------------------
Final Score: 100/100 points
Good job!
----------------------------------------
```
If possible, try to manually test your implementation. Use `./checker.sh` only when you are sure of your result.

1. Implement `rread()` wrapper over `read()`.

   `read()` system call does not guarantee that it will read the requested number of bytes in a single call.
   This happens when the file does not have enough bytes, or when `read()` is interrupted by a signal.
   `rread()` will handle these situations, ensuring that it reads either `num_bytes` or all available bytes.

1. Implement `wwrite()` as a wrapper for `write()`.

   The `write()` system call may not write the requested number of bytes in a single call.
   This happens if `write()` is interrupted by a signal.
   `wwrite()` will guarantee that it wrote the full `num_bytes`, retrying as necessary until all data is successfully written or an error occurs.

1. Implement `cat()`.

   Use `rread()` to read an entire file and `wwrite()` to write the contents to standard output.
   Keep in mind that the buffer size may not fit the entire file at once.

If you're having difficulties solving this exercise, go through [this reading material](../../../reading/file-descriptors.md).
