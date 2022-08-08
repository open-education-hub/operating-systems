module sum_array_threads;

immutable size_t ARR_LEN = 100_000_000;

void calculateArrayPartSum(immutable int[] arr, size_t start, size_t end,
    shared(long[]) results, size_t tid)
{
    long sumArr = 0;
    int* segFaultPtr = null;

    for (size_t i = start; i < end; ++i)
        sumArr += arr[i];

    if (tid == 2)
        *segFaultPtr = 42;

    results[tid] = sumArr;
}


void main(string[] args)
{
    import core.stdc.stdlib : exit;
    import core.thread.threadbase : thread_joinAll;
    import generate_random_array : generateRandomArray;
    import std.algorithm : min;
    import std.concurrency : spawn;
    import std.conv : to;
    import std.datetime.stopwatch : StopWatch;
    import std.math.rounding : ceil;
    import std.stdio : writeln;

    if (args.length < 2)
    {
        writeln("Usage ", args[0], " <num_threads>");
        exit(1);
    }

    immutable int[] arr = generateRandomArray(ARR_LEN);
    int numThreads = args[1].to!int;
    long sumArr = 0;
    shared(long[]) results;
    StopWatch sw;

    results.length = numThreads;
    sw.start();

    for (size_t i = 0; i < numThreads; ++i)
    {
        size_t elemsPerThred = cast(size_t) ceil(
            (cast(double) ARR_LEN) / numThreads);
        size_t start = i * elemsPerThred;
        size_t end = min(ARR_LEN, (i + 1) * elemsPerThred);
        spawn(&calculateArrayPartSum, arr, start, end, results, i);
    }

    thread_joinAll();

    foreach (result; results)
        sumArr += result;

    sw.stop();

    writeln("Array sum is: ", sumArr, "\nTime spent: ", sw.peek.total!"msecs", " ms");
}
