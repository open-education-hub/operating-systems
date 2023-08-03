# Memory Security

Memory security is one of the most important aspects in today's computer systems.
Its main objectives are to avoid the development of vulnerable code and prevent attackers from exploiting existing memory vulnerabilities.
Memory protection techniques are implemented at all levels of memory abstraction: hardware, operating system and programming language.
In addition, third-party software tools may be used to statically and dynamically examine a program to identify vulnerabilities when working with memory.

In this section, we will focus on the main memory vulnerabilities and how to exploit them.
We will use the C programming language for presentation purposes, however, these examples may be reproduced in any language that implements arrays as pointers without bounds and allows the liberal use of pointers.

## Wild Pointer Arithmetic Info Leak

In C, once a pointer has been initialized with a valid address it can potentially access any location of the process address space.
This is problematic for situations where the binary contains sensitive information.
Take for example a server that authenticates users: if the password is stored in some buffer, then if a pointer is wrongfully used, it can end up leaking the password.

Navigate to the `support/memory-security/` directory.
Open and analyze the `buff_leak.c` file.

[Answer this quiz](../quiz/memory-regions-vars.md)

### Practice

The pointer `p` points to the stack, however, we can modify any variable that is declared in the program through `p`.
All we need to know is the offset of the other memory locations that we wish to access.
Run the program and try to input the correct offsets to modify variables from different regions of our program.
Once a correct offset is given as input, the program will output a validation message.

Note that adding or subtracting user provided values to pointers enables an attacker to observe a program's entire memory!

## Buffer Overflow Info Leak

Since arrays decay to pointers in C, the same effect may be obtained by using them.

Navigate to the `support/memory-security/` directory.
Open and analyze the `array_leak.c` file.

Compile and run the program.
Can you extract any information from the output?
Can you identify the return address of the main function?

**Note:** You can use `objdump -d -M intel array_leak` to check the stack layout.
**Note:** Depending on the environment the layout may differ.

Next, open and analyze the `string_leak.c` file.
Compile and run the program.
To better understand the output, use `xxd` to interpret the output as hexadecimal bytes:

```console
student@os:~/.../lab/support/memory-security$ ./string_leak | xxd
```

**Note:** `73` and `6f` are the ascii values of `s` and `o`

[Answer this quiz](../quiz/string-buff-over.md)

### Practice

In file `string_leak.c` replace the usage of `memcpy` with `strcpy`.
Do not modify anything else (including the size of the buffer).
As the name suggests, `strcpy()` is specialized for string copies, therefore we don need to specify how much we want to copy.
What is the result?
Is the result correct?
Explain the result.

[Answer this quiz](../quiz/string-strcpy.md)

## Buffer Overflow Overwrite

Up until this point we have seen how we can exploit a buffer to leak information.
However, this vulnerability may be used most of the time to overwrite data.

Take for example the code in `support/memory-security/bo_write.c`.
Compile and run the code.
What happens?
Why?

[Answer this quiz](../quiz/stack-layout.md)

### Practice

Open the `support/memory-security/bo_write_practice.c` file.
Analyze the code, then compile it and run it.

1. Try to find an input that alters the control flow of the program so that "Comm-link online" is printed.
You are not allowed to modify the source file.

1. Try to find an input that alters the control flow of the program so that "Channel open." is printed.
You are not allowed to modify the source file.

**Note:** Addresses are 8 bytes long on 64 bit machines.

1. Can you think of a different input that results in printing "Comm-link online"?

## ASLR

Address Space Layout Randomization (ASLR) is a protection technique employed by operating systems to make it harder for attackers to identify code locations to jump to.
Essentially, every program section (including shared library code) is mapped at a random virtual address every time the program is run.
That way, it is harder for the attacker to exploit a buffer overflow: the address of a potential code target is different with each run.

To enable randomization, there are 2 steps that need to be taken:

1. Enable ASLR on the operating system.
This enables the operating system to map library code at different virtual addresses in a program.

1. Compile our code as Position Independent Code (PIC).
This instructs the compiler to generate code such that it does not use absolute addresses when calling functions or accessing variables.
As a consequence, the code may be loaded at any given address in memory.

On most Linux systems, ASLR is enabled by default.
Modern compilers generate position independent code by default.

### Practice

Use the `Makefile.aslr` file to compile the `support/memory-security/aslr.c` file:

```console
student@os:~/.../lab/support/memory-security$ make -f Makefile.aslr
```

By default, ASLR and PIC are enabled.
Observe the results.
Next, we disable ASLR:

```console
student@os:~/.../lab/support/memory-security$ echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
```

Even though the code is compiled with PIC, both library and user functions have the same address between runs.
Re-enable ASLR:

```console
student@os:~/.../lab/support/memory-security$ echo 2 | sudo tee /proc/sys/kernel/randomize_va_space
```

Disable PIC by uncommenting the `-fno-PIC` and `LDFLAGS` lines.

We observe that for randomization to work, we need to instruct the OS to randomize the program sections and the compiler to generate code that is position independent.

[Answer this quiz](../quiz/memory-aslr.md)

## Stack Protector

As observed in the previous quiz, ASLR prevents an attacker (most of the times) from discovering a reliable address where to jump to, however, it does not prevent the occurrence of a buffer overflow.
An effective strategy to protect against buffer overflow is represented by the stack protector (or stack canary).
Between the end of the buffer and the return address (below the saved base pointer `rbp`), a random value is placed on the stack.
Before the function returns, the value is checked: if the initial value was modified, then an exception is issued and the program is aborted.

Stack canaries are enabled by default, however, for learning purposes we have disabled it by passing `-fno-stack-protector` to the compiler.

### Practice

Comment the `-fno-stack-protector` switch from the `support/memory-security/Makefile`, recompile and run the `bo_practice_write` executable.
Examine the binary with `objdump` and identify the instructions that set and test the canary.
Observe what happens when a buffer overflow occurs.

[Answer this quiz](../quiz/memory-stack-protector.md)

## Bypassing the Stack Protector

The stack protector is generally placed immediately after the old `rbp`.
With this information we can craft various exploits to bypass it:

- Leak the canary and do not modify it.
Reading the canary, as long as we do not modify it is not going to cause any disturbances.
If we have the canary, we can just include it in our payload and hapily overwrite the return address.

- If we have access to a pointer that we can modify appropriately, we can just jump over the canary and directly modify the return address.

- In case we have multiple buffers defined in the same stack frame, we can simply overwrite data in a buffer that is placed above the buffer we are exploiting without the stack protector intervention.

### Practice

Inspect the `support/memory-security/stack_protector.c` source file.
Compile the program and examine the object code.
Try to identify the canary value.
Using the `addr` variable, write 2 `scanf` instructions: one that overwrites the canary with the corect value and one that overwrites the return address with the address of function `pawned`.
In case of a successful exploit a video will be offered as reward.

[Answer this quiz](../quiz/bypass-canary.md)
