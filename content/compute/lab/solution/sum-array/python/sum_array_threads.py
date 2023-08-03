# SPDX-License-Identifier: BSD-3-Clause

from math import ceil
from random import randint
from sys import argv
from threading import Thread
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
        print(f"Usage: {argv[0]} <num_threads>")
        return 1

    num_threads = int(argv[1])
    arr = generate_random_array()
    sum_arr = 0
    threads = [None] * num_threads
    sums = [None] * num_threads

    time_start = time_ns()

    for i in range(num_threads):
        start = i * ceil(ARR_LEN / num_threads)
        end = min(ARR_LEN, (i + 1) * ceil(ARR_LEN / num_threads))
        threads[i] = Thread(
            target=calculate_array_part_sum, args=(arr, start, end, i, sums)
        )
        threads[i].start()

    for i in range(num_threads):
        threads[i].join()
        sum_arr += sums[i]

    time_end = time_ns()
    time_spent = (time_end - time_start) / 1000_000

    print(f"Array sum is: {sum_arr}; time spent: {time_spent}ms")


if __name__ == "__main__":
    exit(main())
