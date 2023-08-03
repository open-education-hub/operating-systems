# Stack layout

## Question Text

What is the stack layout for the `fun` function in the `bo_write.c` program (starting from a high address)?

## Question Answers

- return address, old `rbp`, maybe some padding, variable `a`, `b[0]`, `b[1]`, `b[2]`

+ return address, old `rbp`, maybe some padding, variable `a`, `b[2]`, `b[1]`, `b[0]`

- return address, maybe some padding, variable `a`, `b[0]`, `b[1]`, `b[2]`

- return address, old `rbp`, maybe some padding, `b[0]`, `b[1]`, `b[2]`, variable `a`

## Feedback

Look at the assembly code and notice the exact layout.
