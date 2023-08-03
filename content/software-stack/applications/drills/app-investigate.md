## App Investigation

Enter the `support/app-investigation/` folder and go through the practice items below.

1. Check to see whether there are statically-linked application executables in the system.
   The `file` command tells if the file passed as argument is a statically-linked executable.
   If you can't find one, install the `busybox-static` package.

1. Look into what [busybox](https://busybox.net/) is and explain why it's custom to have it as statically-linked executable.

1. Run `ldd`, `nm`, `strace`, `ltrace` on a statically-linked application executable.
   Explain the results.
