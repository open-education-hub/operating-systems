import subprocess
from sys import exit
from time import sleep

NUM_SLEEPS = 10


def main():
    # TODO 1: create 10 `sleep 1000` processes using `subprocess.Popen`
    # Use the documentation: https://docs.python.org/3/library/subprocess.html#subprocess.Popen
    for _ in range(NUM_SLEEPS):
        subprocess.Popen(["sleep", "1000"])

    # TODO 2: Make this script also wait for 1000 seconds.
    sleep(1000)


if __name__ == "__main__":
    exit(main())
