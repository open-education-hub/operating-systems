module sum_array_sequential;

immutable size_t ARR_LEN = 100_000_000;

void main()
{
    import generate_random_array : generateRandomArray;
    import std.datetime.stopwatch : StopWatch;
    import std.stdio : writeln;

    immutable int[] arr = generateRandomArray(ARR_LEN);
    long sumArr = 0;
    StopWatch sw;

    sw.start();

    foreach (elem; arr)
        sumArr += elem;

    sw.stop();

    writeln("Array sum is: ", sumArr, "\nTime spent: ", sw.peek.total!"msecs",
        " ms");
}
