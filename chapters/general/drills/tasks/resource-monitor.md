# Resource Monitor

## Scenario

We aim to build a solution to monitor resource usage in computer systems within a network.
On each system, an agent process runs, collecting information locally and transmitting it to a master process running on a dedicated system.
The master process is responsible for sending configurations to the agents and reporting resource (ab)use issues to the administrator or commanding actions for the agents to perform.
The implementation of the agents should be as portable as possible to allow them to run on various platforms/operating systems.

All answers should be justified.

## Questions

1. What resources/information will agents collect to report the overall system status?
How will the configuration that the master process will transmit to the agents look like, schematically?

1. Could you describe the design and implementation idea of an agent?

1. Could you describe the design and implementation idea of the master process?

1. Describe schematically the communication protocol between agent and master: what information is transferred, at what intervals, on what triggers, what happens when there are network issues, or when an agent or master fails?
