# System Process Monitoring Tool

## Scenario

We want to use a continuous system process monitoring tool that is portable across multiple operating systems.
The application shows the resource consumption trends (CPU, memory, disk, network) for all system processes throughout their lifespan.
Information is periodically collected using specific operating system interfaces, and it's stored in a database.

Answer the following questions with "True" or "False" and justify the answer.
Justification should be simple, 2-3 sentences for each answer.

## Questions

1. The application must run in privileged mode.
Answer: True

1. The application must be written in the C language.
Answer: False

1. The application is CPU-intensive.
Answer: False

1. The application will have significantly higher memory consumption than other applications on the system.
Answer: False

1. The application requires IPC interfaces (pipes, shared memory, sockets) to interact with other applications and collect the necessary monitoring information.
Answer: False

1. The application can function, with specific design, on both desktop and mobile systems.
Answer: True

1. The application can only monitor single-threaded processes.
Answer: False

1. The application cannot run in a virtual machine.
Answer: False

1. The application cannot memory-map files.
Answer: False

1. The application benefits from using the buffer cache.
Answer: True

1. The application can be implemented without using synchronization primitives.
Answer: True
