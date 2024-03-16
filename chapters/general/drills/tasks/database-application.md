# Database Application

## Scenario

We aim to run a database application in a containerized solution (Docker, Podman) for ease of deployment and isolation.
Running in a container involves isolating the filesystem (and necessary files), necessary processes, computing resources (CPU, memory, disk), and the network portion.
The database application will be accessible from outside the container through a virtual network.

Answer the following questions with "True" or "False" and justify the answer.
Justification should be simple, 2-3 sentences for each answer.

## Questions

1. The database application can only be implemented as a static executable, not a dynamic one.
Answer: False

1. Within the container, the application will use virtual memory mechanisms.
Answer: True

1. Within the container, the application can use the `fork()` system call.
Answer: True

1. The database application can use pipes to communicate outside the container.
Answer: False

1. Information from the application's filesystem is lost when the container terminates.
Answer: False

1. The application can be multi-threaded.
Answer: True

1. For synchronization, the application can only use mutexes, not spinlocks.
Answer: False

1. Processes within the container do have PIDs.
Answer: False

1. The application in the container can have buffer overflow vulnerabilities.
Answer: True

1. Memory within the container cannot be visible from outside the container, even by a privileged account.
Answer: False

1. The application exclusively spends time in user mode, not in kernel mode.
Answer: False
