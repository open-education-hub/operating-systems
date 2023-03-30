# SPDX-License-Identifier: BSD-3-Clause

import os
import sys
import difflib
from subprocess import Popen, PIPE


VERBOSE = False
TRACED_CALLS = ["os_malloc", "os_calloc", "os_realloc", "os_free", "brk", "mmap", "munmap"]
TESTS = {
    "test-malloc-no-preallocate": 2,
    "test-malloc-preallocate": 3,
    "test-malloc-arrays": 5,
    "test-malloc-block-reuse": 3,
    "test-malloc-expand-block": 2,
    "test-malloc-no-split": 2,
    "test-malloc-split-one-block": 3,
    "test-malloc-split-first": 2,
    "test-malloc-split-last": 2,
    "test-malloc-split-middle": 3,
    "test-malloc-split-vector": 2,
    "test-malloc-coalesce": 3,
    "test-malloc-coalesce-big": 3,
    "test-calloc-no-preallocate": 1,
    "test-calloc-preallocate": 1,
    "test-calloc-arrays": 5,
    "test-calloc-block-reuse": 1,
    "test-calloc-expand-block": 1,
    "test-calloc-no-split": 1,
    "test-calloc-split-one-block": 1,
    "test-calloc-split-first": 1,
    "test-calloc-split-last": 1,
    "test-calloc-split-middle": 1,
    "test-calloc-split-vector": 2,
    "test-calloc-coalesce": 2,
    "test-calloc-coalesce-big": 2,
    "test-realloc-no-preallocate": 1,
    "test-realloc-preallocate": 1,
    "test-realloc-arrays": 3,
    "test-realloc-block-reuse": 3,
    "test-realloc-expand-block": 2,
    "test-realloc-no-split": 3,
    "test-realloc-split-one-block": 3,
    "test-realloc-split-first": 3,
    "test-realloc-split-last": 3,
    "test-realloc-split-middle": 2,
    "test-realloc-split-vector": 2,
    "test-realloc-coalesce": 3,
    "test-realloc-coalesce-big": 1,
    "test-all": 5,
}


class Call:
    replacePairs = {
        "SYS_": "",
        "@SYS": "",
        "@libosmem.so": "",
        "_checked": "",
        "<unfinished ...>": ") = <void>",
        "nil": "0"
    }

    def __init__(self, line: str) -> None:
        for string, replacement in Call.replacePairs.items():
            line = line.replace(string, replacement)

        self.name = line.split("(")[0]
        self.args = line[line.find("(")+1:line.find(")")].replace(" ", "").split(",")
        self.ret = line[line.find("=")+1:].strip()

    def __repr__(self) -> str:
        return f"{self.name} ({self.args}) = {self.ret}"


class SysCall(Call):
    # mmap prot values
    MMAP_PROTS = {
        "PROT_READ": 0x1,
        "PROT_WRITE": 0x2,
        "PROT_EXEC": 0x4,
        "PROT_NONE": 0x0
    }

    # mmap flags values
    MMAP_FLAGS = {
        "MAP_SHARED": 0x01,
        "MAP_PRIVATE": 0x02,
        "MAP_FIXED": 0x10,
        "MAP_ANON": 0x20,
    }

    def __init__(self, line: str) -> None:
        Call.__init__(self, line)
        if self.name == "brk":
            self.args = self.args[:1]
        elif self.name == "munmap":
            self.args = self.args[:2]
        elif self.name == "mmap" and len(self.args) == 4:
            self.args += ["-1", "0"]

        self.args[1:] = [str(int(arg, 16)) if "0x" in arg else arg for arg in self.args[1:]]


class LibCall(Call):
    def __init__(self, line: str, syscalls: list = None) -> None:
        Call.__init__(self, line)
        self.syscalls = syscalls.copy() if syscalls else []

    def __repr__(self) -> str:
        ret = super().__repr__()
        if self.syscalls:
            ret += "\n  " + "\n  ".join([str(s) for s in self.syscalls])
        return ret


def pretty_mmap_args(mmap_syscall: SysCall):
    mmap_syscall.args[2] = " | ".join(list(map(
        lambda x: x[0], filter(lambda prot: int(mmap_syscall.args[2]) & prot[1],
        SysCall.MMAP_PROTS.items())
    )))
    mmap_syscall.args[3] = " | ".join(list(map(
        lambda x: x[0], filter(lambda flag: int(mmap_syscall.args[3]) & flag[1],
        SysCall.MMAP_FLAGS.items())
    )))


def parse_ltrace_output(ltrace_output: str):
    # Filter lines that do not contain traced calls
    lines = list(filter(
        lambda line: any(line.find(tc) != -1 for tc in TRACED_CALLS),
        ltrace_output.splitlines()
    ))
    traced_calls = []
    unfinished_stack = []
    syscalls_batch = []

    # Get heap start
    heap_start = int(SysCall(lines[0]).ret, 16)
    # Get exit status
    exit_status = ltrace_output.splitlines()[-1:]
    for line in ltrace_output.splitlines():
        if 'DBG' in line:
            exit_status = [line[line.rfind('DBG:'):line.rfind(')')]] + exit_status

    # Store addresses
    heap_addresses = {}
    mapped_addresses = {}

    # Extract libcalls and nested syscalls from output
    for line in lines:
        # Syscalls
        if "SYS" in line:
            # Ignore syscalls made outside a library call
            if unfinished_stack:
                syscalls_batch.append(SysCall(line))
                # Update mmap params
                if syscalls_batch[-1].name == "mmap":
                    pretty_mmap_args(syscalls_batch[-1])
            continue

        # Libcalls
        if "<unfinished" in line:
            unfinished_stack.append(line)
        elif "resumed>" in line:
            if not unfinished_stack:
                print("No call to resume")
                sys.exit(-1)

            new_line = unfinished_stack.pop()
            new_line = new_line[:new_line.find("<")] + line[line.find(">")+1:]

            # Only add top level calls
            if not unfinished_stack:
                traced_calls.append(LibCall(new_line, syscalls_batch))
                syscalls_batch.clear()
        elif not unfinished_stack:
            # Add top level libcalls
            traced_calls.append(LibCall(line))

    # Map addresses to relative values
    for libcall in traced_calls:
        # Syscalls
        for syscall in libcall.syscalls:
            # Mapped addresses
            if syscall.name == "mmap" and syscall.ret not in mapped_addresses:
                offset = 1 + len(list(filter(lambda v: "+" not in v, mapped_addresses.values())))
                mapped_addresses[syscall.ret] = f"<mapped-addr{offset}>"
            # Heap addresses
            elif syscall.name == "brk" and syscall.ret not in heap_addresses:
                heap_addresses[syscall.ret] = "HeapStart + " + \
                    hex(int(syscall.ret, 16) - heap_start)

        # Return values
        if libcall.ret not in ["<void>", "0"]:
            # Mapped addresses
            if any(s.name == "mmap" for s in libcall.syscalls):
                key = min(
                    ((key, abs(int(libcall.ret, 16) - int(key, 16))) for key in mapped_addresses),
                    key=lambda x: x[1]
                )[0]
                mapped_addresses[libcall.ret] = mapped_addresses[key]
                offset = int(libcall.ret, 16) - int(key, 16)
                if offset:
                    mapped_addresses[libcall.ret] += f" + {hex(offset)}"
            # Heap addresses
            else:
                heap_addresses[libcall.ret] = "HeapStart + " + \
                    hex(int(libcall.ret, 16) - heap_start)

    return traced_calls, heap_addresses, mapped_addresses, exit_status


def write_test_output(test_name, ltrace_output):
    os.makedirs("out", exist_ok=True)

    traced_calls, heap_addresses, mapped_addresses, exit_status = parse_ltrace_output(ltrace_output)

    # Generate output
    output = "\n".join([str(call) for call in traced_calls])
    for addr, offset in heap_addresses.items():
        output = output.replace(addr, offset)
    for addr, label in mapped_addresses.items():
        output = output.replace(addr, label)

    # Justify name and args
    output = "\n".join(
        [line.split("=")[0].ljust(90) + line[line.find("="):] for line in output.splitlines()] + \
        exit_status
    ) + "\n"

    with (open(os.path.join("out", f"{test_name}.out"), "w+", encoding="ascii")) as fout:
        fout.write(output)


def grade(test_name: str):
    out_path = os.path.join("out", f"{test_name}.out")
    ref_path = os.path.join("ref", f"{test_name}.ref")

    if not os.path.isfile(out_path):
        print(f"Failed to open {out_path}", file=sys.stderr)
        sys.exit(-1)

    if not os.path.isfile(ref_path):
        print(f"Failed to open {ref_path}", file=sys.stderr)
        sys.exit(-1)

    with \
        open(out_path, "r", encoding="ascii") as fout, \
        open(ref_path, "r", encoding="ascii") as fref:
        diffs = list(difflib.unified_diff(fout.readlines(), fref.readlines(), \
            fromfile=out_path, tofile=ref_path, lineterm=""))

        if not diffs:
            print(
                test_name.ljust(33) + 24*"." + f" passed ...   {TESTS[test_name]}",
                file=sys.stderr
            )
            return 1

        print(test_name.ljust(33) + 24*"." + " failed ...   0", file=sys.stderr)
        if VERBOSE:
            print(*diffs[:3], sep="\n", file=sys.stderr)
            print(*diffs[3:], sep="", file=sys.stderr)

    return 0


def run_test(test_name):
    executable = os.path.join("bin", test_name)
    if not os.path.isfile(executable):
        print(f"Failed to open {executable}", file=sys.stderr)
        sys.exit(-1)

    env = os.environ.copy()
    src = os.environ.get("SRC_PATH", "../src")
    env["LD_LIBRARY_PATH"] = src
    with Popen(["ltrace", "-F", ".ltrace.conf", "-S", "-x", "os_*", f"{executable}"], \
        stdout=PIPE, stderr=PIPE, env=env) as proc:
        _, stderr = proc.communicate()

        ltrace_output = stderr.decode("ascii")
        write_test_output(test_name, ltrace_output)


def parse_args():
    global TESTS
    global VERBOSE

    if len(sys.argv) > 3:
        print(f"{sys.argv[0]} <test> <-v>", file=sys.stderr)
        sys.exit(-1)
    elif len(sys.argv) == 3:
        if sys.argv[1] == "-v":
            VERBOSE = True
            TESTS = {sys.argv[2]: 0}
        elif sys.argv[2] == "-v":
            VERBOSE = True
            TESTS = {sys.argv[1]: 0}
        else:
            print(f"{sys.argv[0]} <test> <-v>", file=sys.stderr)
            sys.exit(-1)
    elif len(sys.argv) == 2:
        if sys.argv[1] == "-v":
            VERBOSE = True
        else:
            TESTS = {sys.argv[1]: 0}


if __name__ == "__main__":
    parse_args()

    TOTAL = 0
    for test, score in TESTS.items():
        run_test(test)
        if grade(test):
            TOTAL += score

    print("\nTotal:" + " " * 59 + f" {TOTAL}/100", file=sys.stderr)
