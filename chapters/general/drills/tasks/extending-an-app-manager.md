# Extending an App Manager

## Scenario

We want to extend the functionality of an application manager (a program that runs and manages executables).
We want to add functionality to the application manager through which we can transfer a process managed by it from one system to another system managed by another application manager while the process is running.
For simplicity, we consider that the process does not use files from the disk.

All answers should be justified.

## Questions

1. How do you establish the connection and transfer between managers?
Describe a minimal communication protocol.

1. What process data needs to be transferred so that the process can continue running (from where it left off) on the new system?

1. How do you minimize the time the process is stopped?
