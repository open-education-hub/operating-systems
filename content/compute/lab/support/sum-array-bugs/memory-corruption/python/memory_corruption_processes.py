# SPDX-License-Identifier: BSD-3-Clause

from math import ceil
from multiprocessing import Manager, Process
from random import randint, seed
from sys import argv

ARR_LEN = 10_000_000
RANDOM_SEED = 42


def generate_random_array(length=ARR_LEN):
    seed(RANDOM_SEED)
    return [randint(1, 100) for _ in range(length)]


def calculate_array_part_sum(arr, start, end, id, sums):
    sum_arr = 0
    for i in range(start, end):
        sum_arr += arr[i]
    sums[id] = sum_arr


def corrupt_array(arr):
    for i in range(len(arr)):
        arr[i] = -1000


def main():
    if len(argv) < 2:
        print(f"Usage: {argv[0]} <num_processes> [do_corruption]")
        return 1

    num_procs = int(argv[1])
    arr = generate_random_array()
    sum_arr = 0
    procs = [None] * num_procs
    sums = Manager().dict()

    if len(argv) >= 3:
        Process(target=corrupt_array, args=(arr,)).start()

    for i in range(num_procs):
        start = i * ceil(ARR_LEN / num_procs)
        end = min(ARR_LEN, (i + 1) * ceil(ARR_LEN / num_procs))
        procs[i] = Process(
            target=calculate_array_part_sum, args=(arr, start, end, i, sums)
        )
        procs[i].start()

    for i in range(num_procs):
        procs[i].join()
        sum_arr += sums[i]

    print(f"Array sum is: {sum_arr}")


if __name__ == "__main__":
    exit(main())
