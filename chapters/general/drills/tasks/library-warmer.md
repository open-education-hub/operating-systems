# Library Warmer

## Scenario

The concept of "cold start" refers to starting a process for the first time.
In this situation, during the initial start-up, the executable of the process, data/configuration files and dynamic libraries used need to be loaded for the first time.
A "hot/warm start" implies that some of this information is already loaded into memory, resulting in a faster start-up of the process.

We aim to implement an application for "warming up" the start-up of processes by loading the dynamic libraries used by these processes.
This system involves a process that loads, according to a strategy, the commonly used libraries of applications to facilitate a "warm start" of the applications.

The "warming up" application will monitor the usage of dynamic libraries in the system by system processes and decide which libraries need to be "warmed up" for future application launches.

All answers should be justified.

## Questions

1. Describe schematically what the components of the heating application are.
What is the execution flow of the application?

1. What functionalities does the operating system need to expose in order to efficiently and effectively implement the heating application?

1. What configuration interface will the application expose to the user/system administrator?
What will they be able to configure?

1. How will you evaluate the use of the heating application?
What will you measure to demonstrate an improvement (or not) compared to the case where you do not use the application?
