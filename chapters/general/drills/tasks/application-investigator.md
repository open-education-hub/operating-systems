# Application Investigator

## Scenario

We aim to investigate, for security/forensics reasons, applications running on a system.
For this purpose, we design an application that, given a PID (or equivalent), suspends the execution of the target process and dumps the memory of that process into a file, using a dedicated interface of the operating system.

Answer the following questions with "True" or "False" and justify the answer.
Justification should be simple, 2-3 sentences for each answer.

## Questions

1. The application runs in privileged mode.
Answer: True

1. The suspended process must be single-threaded.
Answer: False

1. The application uses an IPC interface to communicate with the process after it has been suspended.
Answer: False

1. Dumping can only be done in read-only or read-execute areas, not in read-write areas.
Answer: False

1. The most frequently used system call of the application is `write()`.
Answer: True

1. The application would benefit from a multi-threaded implementation.
Answer: False

1. The application can function in a virtual machine.
Answer: True

1. The application does not perform context switches.
Answer: False

1. The application benefits from increasing the size of the file descriptor table.
Answer: False

1. The resulting file from the memory dump is a binary file, not text.
Answer: True

1. In principle, with certain adjustments, the application can work on both 32-bit and 64-bit systems.
Answer: True
