# SPDX-License-Identifier: BSD-3-Clause

from math import ceil
from multiprocessing import Manager, Process
from random import randint
from sys import argv
from time import time_ns

ARR_LEN = 10_000_000


def generate_random_array(length=ARR_LEN):
    return [randint(1, 100) for _ in range(length)]


def calculate_array_part_sum(arr, start, end, id, sums):
    sum_arr = 0
    for i in range(start, end):
        sum_arr += arr[i]
    sums[id] = sum_arr


def main():
    if len(argv) < 2:
        print(f"Usage: {argv[0]} <num_processes>")
        return 1

    num_procs = int(argv[1])
    arr = generate_random_array()
    sum_arr = 0
    procs = [None] * num_procs
    sums = Manager().dict()

    time_start = time_ns()

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

    time_end = time_ns()
    time_spent = (time_end - time_start) / 1000_000

    print(f"Array sum is: {sum_arr}; time spent: {time_spent}ms")


if __name__ == "__main__":
    exit(main())
