# Intrusion Detection System

## Scenario

We want to build an intrusion detection system for applications serving different servers without having access to their source code.
Assume that we have access to a knowledge base (in any form you prefer) describing the normal behavior of the application.

All answers should be justified.

## Questions

1. What profiling and debugging utilities (`perf`, `strace`, `valgrind`, etc.) can help us verify whether, as a result of interaction between the server and a specific client, the client was able to exploit various vulnerabilities such as buffer overflow or code injection?

1. Could you propose a simplistic algorithm that can determine the type of client behavior (normal or malicious) based on information gathered from the utility of your choice?
