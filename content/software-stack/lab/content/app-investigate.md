# App Investigation

Let's spend some time investigating actual applications residing on the local system.
For now, we know that applications are developed using high-level languages and then compiled or interpreted to use the lower-layer interfaces of the software stack, such as the system call API.

Let's enter the `support/app-investigate/` folder and run the `get_app_types.sh` script:

```console
student@os:~/.../lab/support/app-investigate$ ./get_app_types.sh
binary apps: 2223
Perl apps: 256
Shell apps: 454
Python apps: 123
Other apps: 27
```

The script prints the types of the application executables in the system.
The output will differ between systems, given each has particular types of applications installed.

We list them by running the command inside the `get_app_types.sh` script:

```console
student@os:~/.../lab/support/app-investigate$ find /usr/bin /bin /usr/sbin /sbin -type f -exec file {} \;
[...]
/usr/bin/qpdldecode: ELF 64-bit LSB shared object, x86-64 [...]
/usr/bin/mimeopen: Perl script text executable
[...]
```

As above, the output will differ between systems.

So, depending on the developers' choice, applications may be:

* compiled into executables, from compiled languages such as C, C++, Go, Rust, D
* developed as scripts, from interpreted languages such as Python, Perl, JavaScript

## Practice

Enter the `support/app-investigate/` folder and go through the practice items below.
Select a binary executable application and a scripted application from those listed above.

1. Use `ldd` on the two applications.
   Notice the resulting messages and explain the results.

1. Use `ltrace` and `strace` on the two applications.
   Follow the library calls and the system calls done by each application.
