// SPDX-License-Identifier: BSD-3-Clause

module sum_array_processes;

immutable size_t ARR_LEN = 100_000_000;

void calculateArrayPartSum(immutable int[] arr, size_t start, size_t end,
    long[] results, size_t tid)
{
    long sumArr = 0;
    int* segFaultPtr = null;

    for (size_t i = start; i < end; ++i)
        sumArr += arr[i];

    if (tid == 2)
        *segFaultPtr = 42;

    results[tid] = sumArr;
}

long[] createSharedResultsArray(size_t numProcesses)
{
    import core.sys.posix.sys.mman;

    // This buffer will be shared by the process that creates it and all its
    // children due to the `MAP_SHARED` argument
    return (cast(long*) mmap(null, numProcesses * long.sizeof,
        PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0))
        [0 .. numProcesses];
}

void main(string[] args)
{
    import generate_random_array : generateRandomArray;
    import std.algorithm : min;
    import std.conv : to;
    import core.stdc.stdlib : exit;
    import core.sys.posix.sys.wait;
    import core.sys.posix.unistd : fork, pid_t;
    import std.datetime.stopwatch : StopWatch;
    import std.math.rounding : ceil;
    import std.stdio : writeln;

    if (args.length < 2)
    {
        writeln("Usage ", args[0], " <num_processes>");
        exit(1);
    }

    immutable int[] arr = generateRandomArray(ARR_LEN);
    int numProcesses = args[1].to!int;
    int status;
    long sumArr = 0;
    long[] results = createSharedResultsArray(numProcesses);
    pid_t[] children;
    StopWatch sw;

    results.length = numProcesses;
    children.length = numProcesses;
    sw.start();

    for (size_t i = 0; i < numProcesses; ++i)
    {
        size_t elemsPerThred = cast(size_t) ceil(
            (cast(double) ARR_LEN) / numProcesses);
        size_t start = i * elemsPerThred;
        size_t end = min(ARR_LEN, (i + 1) * elemsPerThred);

        // Spawn another process with the current one as its parent.
        children[i] = fork();
        switch(children[i])
        {
        case -1:
            exit(1);
        case 0:
            calculateArrayPartSum(arr, start, end, results, i);
            exit(0);
        default:
            continue;
        }
    }


    for (size_t i = 0; i < numProcesses; ++i)
    {
        waitpid(children[i], &status, 0);
        if (WIFEXITED(status))
            writeln("Process ", i, " ended with exit code ",
                WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            writeln("Process ", i, " was killed by signal ", WTERMSIG(status));

        sumArr += results[i];
    }

    sw.stop();

    writeln("Array sum is: ", sumArr, "\nTime spent: ", sw.peek.total!"msecs",
        " ms");
}
