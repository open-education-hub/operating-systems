# Industrial System

## Scenario

We aim to develop an industrial system that will run distributed applications in the web assembly format, a binary code (bytecode) that requires an executor called wasmer (similar to Java Virtual Machine) to run.
Applications can be written in any language that can generate web assembly code.
One of the compilers that can generate web assembly code is LLVM.
Wasmer allows the use of any existing libraries on the system it runs on, requiring adaptation libraries (glue code).

Answer the following questions with "True" or "False" and justify the response.
Justification should be simple, 2-3 sentences for each response.

## Questions

1. The startup of each application is more efficient on POSIX systems.
Answer: True

1. A JIT system is a system that allows for the compilation of parts of an application to be executed directly on the processor when needed.
By integrating a JIT compiler into wasmer, the performance of applications using graphical interfaces, which in turn use the OpenGL libraries of the operating system, has increased.
Answer: False

1. Applications can use both types of threads, kernel, and user.
Answer: True

1. Applications can always use UNIX sockets for communication.
Answer: False

1. Communication between two threads, regardless of the application they are in, is possible via signals.
Answer: False

1. The operating system mandates wasmer to use garbage collection.
Answer: False

1. As a virtual executor, wasmer does not use memory paging.
Answer: False

1. Wasmer can simulate the functioning of a container.
Answer: True

1. An IO Intensive application will run efficiently on wasmer.
Answer: True

1. Context switching is more costly for applications in wasmer.
Answer: False

1. Applications in wasmer do not use the libc file access API but still benefit from the file cache system of the operating system.
Answer: True
