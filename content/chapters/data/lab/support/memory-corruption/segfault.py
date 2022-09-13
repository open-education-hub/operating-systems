#!/usr/bin/env python3

# SPDX-License-Identifier: BSD-3-Clause

"""
Demonstrate lack of memory exceptions (i.e. segmentation fault) in Python
"""

SIZE_INT = 32


def print_bit_array(bits):
    """Print array of bits."""
    i = SIZE_INT - 1
    while i >= 0:
        print(bits[i])
        i = i - 1


def to_bits(value, bits):
    """Convert integer value to bit array."""
    shift_bit = 1
    for i in range(SIZE_INT):
        if value & shift_bit == 0:
            bits[i] = 0
        else:
            bits[i] = 1
        shift_bit = shift_bit << 1


def factorial(num):
    """Compute factorial of num (i.e. num!)."""
    result = 0
    if num == 0:
        return 1
    result = factorial(num - 1)
    return result * num


number = input("Input a positive integer: ")
fact = factorial(int(number))
print(number, " Factorial =", fact)
the_bits = [0] * SIZE_INT
to_bits(fact, the_bits)
print_bit_array(the_bits)
