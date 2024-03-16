# Network Configurations Manager

## Scenario

We aim to implement an application to run on a home router (Wi-Fi router) to manage network configurations: routing, port forwarding, firewall, Wi-Fi security, etc.
The router runs a modern operating system - rich OS, like Linux.
Other applications, such as a web service providing a user web interface, will interact with the configuration application through IPC mechanisms to query the state of network configurations and/or modify them.

Answer the following questions with "True" or "False" and justify the answer.
Justification should be simple, 2-3 sentences for each answer.

## Questions

1. The application must be written entirely in a compiled language like C/C++/Rust.
Answer: False

1. The application can be multi-threaded.
Answer: True

1. The application is portable to other operating systems.
Answer: False

1. The application must run in privileged mode.
Answer: True

1. For security reasons, the application cannot use demand paging.
Answer: False

1. The application does not have a file descriptor table.
Answer: False

1. Interaction between the application and other services (such as the web) can be achieved through anonymous pipes.
Answer: False

1. The application is CPU intensive.
Answer: False

1. Two instances of the application can be started on the system.
Answer: True

1. In the application's address space, there are memory areas without write permissions.
Answer: True

1. The application process will consistently have the highest priority.
Answer: False
