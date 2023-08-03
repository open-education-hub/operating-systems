# SPDX-License-Identifier: BSD-3-Clause

FILE_NAME = "file.txt"


def read_file(file_name):
    # "r" is the default mode for openng files: for reading.
    # `f` is a handler to the file.
    f = open(file_name, "r")
    content = f.read()
    print(f"File contents are: {content}")
    f.close()


def write_file(file_name):
    # "w" is the mode for writing to the file.
    # `f` is a handler to the file.
    f = open(file_name, "w")
    f.write("Python was here!")
    print("Wrote new data to file")
    f.close()


def main():
    read_file(FILE_NAME)
    write_file(FILE_NAME)
    read_file(FILE_NAME)


if __name__ == "__main__":
    exit(main())
