# Digital Forensics

## Scenario

For digital forensics operations (digital evidence investigation), we want to develop an application that dumps the entire physical memory (RAM) of a modern operating system (such as Linux, Windows, macOS).
We assume there is a dedicated interface of the operating system that allows reading of physical memory for dumping.
The application can dump to a file or to standard output (for redirection to a file or network redirection).
The result is a dump with the size of the physical memory (RAM) of the system.

Answer the following questions with "True" or "False" and justify your answer.
The justification should be simple, 2-3 sentences for each answer.

## Questions

1. The application must be run in privileged mode, as root.
Answer: True

1. During its execution, the application does not make system calls.
Answer: False

1. The application will benefit from a multithreaded implementation.
Answer: True

1. The memory dump will contain information about the application itself.
Answer: True

1. At runtime, the application will use network sockets.
Answer: False

1. Two instances of the application CANNOT run simultaneously on the same system.
Answer: False

1. In its implementation, the application must use synchronization primitives.
Answer: False

1. The application must be implemented in the form of a static executable.
Answer: False

1. During its execution, the application uses the virtual memory mechanism.
Answer: True

1. The application cannot realistically be used on a 64-bit system, only on a 32-bit system.
Answer: False

1. As long as the operating system provides support, the application can work on both x86 and ARM processor architectures.
Answer: False
