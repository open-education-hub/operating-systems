# Distributed system

## Scenario

We are designing a distributed e-learning system across multiple servers.
The system consists of frontend services to handle client requests (for example, when a client accesses https://curs.upb.ro) and backend services for information storage.

Respond to the following questions with "True" or "False" and provide reasoning for each answer.
The explanation should be concise, 2-3 sentences for each response.

## Questions

1. The backend service will benefit from the use of buffer cache.
Answer: True

1. The frontend application must necessarily be multi-threaded.
Answer: False

1. Both components (frontend and backend) are I/O intensive.
Answer: True

1. Communication between backend services on different servers can be achieved through shared memory.
Answer: False

1. If a backend service becomes unavailable, the entire system becomes unusable.
Answer: False

1. The frontend service predominantly uses socket file descriptors, while backend services predominantly use file descriptors.
Answer: True

1. Both types of services need to run on a UNIX-based operating system (Linux, FreeBSD).
Answer: False

1. Exclusive access primitives are needed for communication between frontend and backend.
Answer: False

1. A higher processor load is expected for the frontend compared to the backend.
Answer: False

1. SSD storage is required for the frontend service.
Answer: False

1. The backend service uses a lot of memory - almost the entire system memory.
Answer: True
