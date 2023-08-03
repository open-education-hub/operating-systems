// SPDX-License-Identifier: BSD-3-Clause

module generate_random_array;

immutable int MAX_ELEM = 1000;
immutable int RANDOM_SEED = 42;

immutable(int[]) generateRandomArray(size_t length)
{
    import std.algorithm.iteration : map;
    import std.array : array;
    import std.random : Random, uniform;
    import std.range : iota;

    auto rnd = Random(RANDOM_SEED);

    return array(iota(0, length)
        .map!(_ => cast(immutable int) uniform(0, MAX_ELEM, rnd)));
}
