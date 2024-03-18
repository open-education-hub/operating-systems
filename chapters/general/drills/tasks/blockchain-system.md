# Blockchain System

## Scenario

A blockchain system can be viewed as a database replicated across multiple nodes (each node having its own operating system) distributed in different locations.
All nodes start with exactly the same user database.
There are frontend services to handle client requests (e.g., transferring from Alice to Bob).
The backend service, each node receives the same transaction and applies changes to its own local database (subtracting from Alice's wallet variable and adding to Bob's wallet variable).
Finally, there's a consensus stage where it's checked if the majority of nodes have the same database in the end.
If yes, the action is retained.
Otherwise, it's canceled.

Answer the following questions with "True" or "False" and justify the response.
Justification should be simple, 2-3 sentences for each response.

## Questions

1. At the node level, transaction execution will benefit from using the buffer cache.
Answer: True

1. The frontend services are I/O intensive.
Answer: True

1. The backend service is I/O intensive.
Answer: True

1. For the consensus routine, communication between nodes can be done through shared memory.
Answer: False

1. If a node becomes unavailable, the entire system becomes unusable.
Answer: False

1. The frontend service predominantly uses socket file descriptors.
Answer: True

1. The backend service predominantly uses file descriptors of type file.
Answer: True

1. All nodes need to use the same operating system to communicate and synchronize.
Answer: False

1. If consensus is reached, all nodes will write the obtained result into the database.
Synchronization mechanism is needed for this write.
Answer: False

1. An SSD (fast storage) is more useful for the frontend service than for the backend.
Answer: False

1. The backend service uses a lot of RAM (almost the entire system memory).
Answer: True
