# FaaS Application

## Scenario

We aim to implement a Function as a Service (FaaS) type service.
This service exposes a REST network API.
With this API, network clients can order the remote execution of programs.
A client sends the program written in a given programming language to be remotely executed, along with the program's arguments.
The FaaS service runs the program and transmits the result to the client.

Respond to the following questions with "True" or "False" and justify the answer.
The justification should be simple, 2-3 sentences for each response.

## Questions

1. The service uses shared memory to interact with clients.
Answer: False

1. The service can run distributed, with client requests being redirected to multiple execution systems.
Answer: True

1. For security reasons, programs (functions) are executed in isolated contexts, within containers or virtual machines.
Answer: True

1. In handling requests, the service will benefit from an implementation with a thread pool.
Answer: True

1. During its execution, the service does NOT generate involuntary context switches.
Answer: False

1. Among processor, memory, network, and disk resources, the service uses the least disk.
Answer: True

1. The service does NOT consume file descriptors outside of the standard descriptors 0, 1 and 2.
Answer: False

1. The service would lead to significant performance improvements if implemented in a low-level language like C compared to a high-level one like Python.
Answer: False

1. To serve requests and execute programs sent by clients, the service will start new processes.
Answer: True

1. During the execution of the service, NO hardware interrupts are generated.
Answer: False

1. The service can only operate on a Linux operating system.
Answer: False
