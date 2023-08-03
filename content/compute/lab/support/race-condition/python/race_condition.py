# SPDX-License-Identifier: BSD-3-Clause

from threading import Thread

NUM_ITER = 10_000_000
var = 0


def increment_var():
    global var
    for _ in range(NUM_ITER):
        var += 1


def decrement_var():
    global var
    for _ in range(NUM_ITER):
        var -= 1


def main():
    t1 = Thread(
        target=increment_var,
    )
    t2 = Thread(
        target=decrement_var,
    )

    t1.start()
    t2.start()

    t1.join()
    t2.join()

    print(f"var = {var}")


if __name__ == "__main__":
    exit(main())
