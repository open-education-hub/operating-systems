// SPDX-License-Identifier: BSD-3-Clause

module sum_array_threads_reduce;

immutable size_t ARR_LEN = 100_000_000;

void main(string[] args)
{
    import generate_random_array : generateRandomArray;
    import std.conv : to;
    import std.datetime.stopwatch : StopWatch;
    import std.parallelism : TaskPool;
    import core.stdc.stdlib : exit;
    import std.stdio : writeln;

    if (args.length < 2)
    {
        writeln("Usage ", args[0], " <num_threads>");
        exit(1);
    }

    immutable int[] arr = generateRandomArray(ARR_LEN);
    int numThreads = args[1].to!int;
    TaskPool taskPool = new TaskPool(numThreads);
    StopWatch sw;

    sw.start();

    long sumArr = taskPool.reduce!"a + b"(0L, arr);

    sw.stop();

    writeln("Array sum is: ", sumArr, "\nTime spent: ", sw.peek.total!"msecs", " ms");
    taskPool.stop();
}
