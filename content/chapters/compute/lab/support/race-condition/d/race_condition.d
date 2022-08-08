module race_condition;

enum NUM_ITER = 10_000_000;

__gshared int var;

void incrementVar()
{
    for (size_t i = 0; i < NUM_ITER; i++)
        var++;
}

void decrementVar()
{
    for (size_t i = 0; i < NUM_ITER; i++)
        var--;
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
