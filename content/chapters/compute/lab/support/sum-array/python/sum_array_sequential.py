# SPDX-License-Identifier: BSD-3-Clause

from random import randint
from time import time_ns

ARR_LEN = 10_000_000


def generate_random_array(length=ARR_LEN):
    return [randint(1, 100) for _ in range(length)]


def main():
    arr = generate_random_array()
    sum_arr = 0
    time_start = time_ns()

    for elem in arr:
        sum_arr += elem

    time_end = time_ns()
    time_spent = (time_end - time_start) / 1000_000

    print(f"Array sum is: {sum_arr}; time spent: {time_spent}ms")


if __name__ == "__main__":
    exit(main())
