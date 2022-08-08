module race_condition_atomic;

import core.atomic;

enum NUM_ITER = 10_000_000;

shared int var;

void incrementVar()
{
    for (size_t i = 0; i < NUM_ITER; i++)
    {
        // var += 1
        atomicOp!"+="(var, 1);
    }
}

void decrementVar()
{
    for (size_t i = 0; i < NUM_ITER; i++)
    {
        // TODO: Use `atomicOP` to implement `var -= 1` atomically.

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
