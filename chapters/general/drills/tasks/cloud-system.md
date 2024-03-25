# Cloud System

## Scenario

We are designing a cloud system to run microservices using small virtual machines (microVMs).
The system consists of "executor" nodes that store and run the virtual machines and a "dispatcher" node that distributes requests to the "executor" nodes.

Executor nodes can stop, suspend, start, or resume virtual machines based on requests received from the dispatcher.
Suspension can occur either in RAM or on disk.

All answers should be justified.

## Questions

1. Describe the criteria based on which the dispatcher will send requests to the executors and how it obtains/measures the necessary metrics.

1. What usage scenarios are suitable for such a cloud system?
In these scenarios, when does the starting/resuming and stopping/suspending of a virtual machine occur?

1. How does an executor node decide which method to use: stopping, suspending in RAM, or suspending on disk?
What criteria does it use, and how does it use them in the decision-making process?

1. How will you calculate the billing for the system's customers?
