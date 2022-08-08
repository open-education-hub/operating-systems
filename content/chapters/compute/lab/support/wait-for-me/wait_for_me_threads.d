module wait_for_me_threads;

const ARR_LEN = 400;

void negateArray(shared(int[]) arr)
{
    for (size_t i = arr.length - 1; i != -1; --i)
        arr[i] = -arr[i];
}

void main()
{
    import std.stdio : writeln;

    shared(int[]) arr;
    arr.length = ARR_LEN;

    for (int i = 0; i < ARR_LEN; ++i)
        arr[i] = i + 1;

    // TODO: Call the `negateArray()` function in a separate thread.`

    writeln(arr);
}
