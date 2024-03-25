# Web GUI 2

## Scenario

`Node.js` is a programming platform that exposes the JavaScript language for programs of any kind, not just for the browser.
This platform has several important properties:

- It provides programmers access to most functions offered by the operating system libraries.
- It offers programmers a single execution thread.
- It provides programmers with a method to add native libraries.

All answers should be justified.

## Questions

1. `Node.js` supports concurrency (simulating parallelism), which is why it is used for writing web servers.
Explain how the platform's engine achieves this.

1. When using `Node.js`, what are the restrictions (in terms of interacting with the operating system)?

1. Propose an improvement to the platform to support parallelism (parallel processing).
Take into account that the JavaScript engine (V8) can only execute JavaScript code on a single thread.
You cannot modify the V8 engine.

1. Answer one of the following:

- `Node.js` (V8) uses a Just-in-time compiler, compiling the most frequently used parts of JavaScript code for the processor.
Describe the architecture of this system and explain how it interacts with the operating system on the computer it runs on.
- Explain the necessity of using trait bounds in Rust.
