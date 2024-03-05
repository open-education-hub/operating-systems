# App Investigation

Enter the `app-investigation/support/` folder and go through the practice items below.
Select a binary executable application and a scripted application.

1. Use `ldd` on the two applications.
   Notice the resulting messages and explain the results.

1. Use `ltrace` and `strace` on the two applications.
   Follow the library calls and the system calls done by each application.

1. Check to see whether there are statically-linked application executables in the system.
   The `file` command tells if the file passed as argument is a statically-linked executable.
   If you can't find one, install the `busybox-static` package.

1. Look into what [busybox](https://busybox.net/) is and explain why it's custom to have it as statically-linked executable.

1. Run `ldd`, `nm`, `strace`, `ltrace` on a statically-linked application executable.
   Explain the results.

If you're having difficulties solving this exercise, go through [this](../../../reading/app-investigate.md) reading material.
