# Web GUI 1

## Scenario

Since most graphical interfaces today are implemented as browser-based applications, we want to create a system that allows the use of web technologies (HTML/CSS/JavaScript) to build applications that run directly on the operating system.
The idea is to unify the way graphical interface applications are written, so there is no need to rewrite applications for each platform.

We start from the following premises:

- Each operating system has its own libraries for graphical interfaces, which can display web pages and run JavaScript code.
- Applications do not necessarily have to be written in a single programming language.
- No one wants to write applications in C/C++.

All answers should be justified.

## Questions

1. Propose an architecture for such a system so that any kind of desktop application can be written.
Describe the general components and their interaction.
Applications should be able to access system resources.

1. We want to add the possibility of having threads in the application.
Propose an architecture for this.

1. Propose a mechanism that will allow the use of async and await primitives for functions that interact with the operating system.

1. Answer one of the two options:

- What security elements should we be aware of when implementing such a system?
- Explain the necessity of using lifetimes in Rust.
