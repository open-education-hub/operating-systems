# Memory Deduplication

## Scenario

Memory deduplication is a technique commonly used in virtualized environments to reduce the memory footprint by employing a single instance of different memory areas for multiple virtual machines.
Let's assume we have a custom operating system running on a specialized environment that lacks support for dynamic libraries due to efficient design reasons.
It runs applications solely from static executables.
We aim to have memory deduplication support for applications running on this operating system.

All answers should be justified.

## Questions

1. Describe schematically which components of the system are involved in the memory deduplication part.
Describe the flow through which applications are built and executed to benefit from memory deduplication.

1. Describe the particularities of the build process (compilation, linking, etc.) that create static executables used for deduplication at runtime.

1. Describe the functionalities of the operating system and the runtime environment that allow memory deduplication.
When and how will memory deduplication be performed with the support of the operating system?

1. How do we evaluate the functionality of memory deduplication?
What metrics do we track?
What scenarios will we use to monitor these metrics?
