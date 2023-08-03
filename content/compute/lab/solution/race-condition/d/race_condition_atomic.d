// SPDX-License-Identifier: BSD-3-Clause

module race_condition_atomic;

import core.atomic;

enum NUM_ITER = 10_000_000;

shared int var;

void incrementVar()
{
    for (size_t i = 0; i < NUM_ITER; i++)
    {
        // var += 1
        // `atomicOp` is a template function. It can perform any simple
        // operation, such as `+=`, &= or `-=`, atomically. The operations is
        // given to the function as a template argument using the following
        // construction: !"+=". The values in parantheses are the operands
        // of the atomic operation.
        atomicOp!"+="(var, 1);
    }
}

void decrementVar()
{
    for (size_t i = 0; i < NUM_ITER; i++)
    {
        // TODO: Use `atomicOP` to implement `var -= 1` atomically.
        atomicOp!"-="(var, 1);
    }
}

void main()
{
    import core.thread.threadbase : thread_joinAll;
    import std.concurrency : spawn;
    import std.stdio : writeln;

    spawn(&incrementVar);
    spawn(&decrementVar);

    thread_joinAll();

    writeln("var = ", var);
}
