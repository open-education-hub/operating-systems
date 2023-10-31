import argparse
import os
import re
import sys
import difflib
import dataclasses
from subprocess import Popen, PIPE


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


class UnfinishedCall(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class Call:
    def __init__(self, line: str, resumed_line: str = None) -> None:
        if resumed_line:
            line = re.sub(r"<.*\)", ")", line + resumed_line)

        if "unfinished" in line:
            raise UnfinishedCall()

        self.name = line.split("(")[0]
        self.args = (
            line[line.find("(") + 1 : line.find(")")].replace(" ", "").split(",")
        )
        self.ret = line[line.find("=") + 1 :].strip()
        self.nested_calls = []

    def add_nested_calls(self, nested_calls: list = None) -> None:
        self.nested_calls = nested_calls.copy() if nested_calls else []

    def prettify(self, heap_start, mmaps: dict) -> str:
        self.args = list(
            map(
                lambda arg: self.interpret_addr(arg, heap_start, mmaps),
                self.args,
            )
        )
        self.ret = self.interpret_addr(self.ret, heap_start, mmaps)

        if self.name == "mmap":
            self.interpret_mmap_args()

    @staticmethod
    def interpret_addr(addr: str, heap_start: int, mmaps: dict) -> str:
        if "0x" in addr:
            heap_addr = "HeapStart + " + hex(int(addr, 16) - heap_start)
            return mmaps.get(addr, heap_addr)

        return addr

    def interpret_mmap_args(self) -> str:
        mmap_prots = {
            "PROT_READ": 0x1,
            "PROT_WRITE": 0x2,
            "PROT_EXEC": 0x4,
            "PROT_NONE": 0x0,
        }

        mmap_flags = {
            "MAP_SHARED": 0x01,
            "MAP_PRIVATE": 0x02,
            "MAP_FIXED": 0x10,
            "MAP_ANON": 0x20,
        }

        self.args[2] = " | ".join(
            list(
                map(
                    lambda x: x[0],
                    filter(
                        lambda prot: int(self.args[2]) & prot[1],
                        mmap_prots.items(),
                    ),
                )
            )
        )
        self.args[3] = " | ".join(
            list(
                map(
                    lambda x: x[0],
                    filter(
                        lambda flag: int(self.args[3]) & flag[1],
                        mmap_flags.items(),
                    ),
                )
            )
        )

    def __repr__(self) -> str:
        ret = f"{self.name} ({self.args}) = {self.ret}"
        if self.nested_calls:
            ret += "\n  " + "\n  ".join([str(s) for s in self.nested_calls])
        return ret


class LtraceParser:
    REPLACE_DICT = {
        "SYS_": "",
        "@SYS": "",
        "@libosmem.so": "",
        "_checked": "",
        "nil": "0",
    }

    TRACED_CALLS = [
        "os_malloc",
        "os_calloc",
        "os_realloc",
        "os_free",
        "brk",
        "mmap",
        "munmap",
    ]

    def __init__(self, program_output, output) -> None:
        raw_lines = output.splitlines()
        for string, replacement in LtraceParser.REPLACE_DICT.items():
            raw_lines = list(
                map(lambda line: line.replace(string, replacement), raw_lines)
            )

        linker_brk = Call(raw_lines[0])
        self.heap_start = int(linker_brk.ret, 16)

        self.exit_status = list(
            filter(
                lambda line: line.startswith("+++") or line.startswith("DBG:"),
                raw_lines,
            )
        )

        self.lines = list(filter(lambda line: self.is_line_valid(line), raw_lines))
        self.line_index = 0

        self.mmaps = {}
        self.mmaps_count = 1
        self.block_size = 0x20

        self.program_output = self.pretty_print_program_output(program_output)

    def pretty_print_program_output(self, program_output) -> str:
        formatted_output = ""
        for line in program_output.splitlines():
            formatted_output += (
                " ".join(
                    list(map(lambda word: self.prettify_address(word), line.split()))
                )
                + "\n"
            )
        return formatted_output

    def prettify_address(self, addr: str) -> str:
        if "0x" in addr:
            addr = addr.strip(",")
            heap_addr = "HeapStart + " + hex(int(addr, 16) - self.heap_start) + ","
            return self.mmaps.get(addr, heap_addr)

        return addr

    @staticmethod
    def is_line_valid(line: str):
        # Ignore nested libcalls
        if line.startswith(" ") and (
            line.strip().startswith("os_") or line.strip().startswith("<")
        ):
            return False

        # Ignore top level syscalls
        if (
            line.startswith("brk")
            or line.startswith("mmap")
            or line.startswith("munmap")
        ):
            return False

        return any(call in line for call in LtraceParser.TRACED_CALLS)

    def parse_libcall(self):
        if self.line_index >= len(self.lines):
            return None

        libcall_start = self.lines[self.line_index]
        libcall_end = None
        syscalls = []

        self.line_index += 1
        while self.line_index < len(self.lines):
            line = self.lines[self.line_index]

            if line.startswith("os_"):
                break

            if line.startswith("<..."):
                libcall_end = line
                self.line_index += 1
                break

            if line.startswith(" "):
                syscalls.append(Call(line.strip()))
                if syscalls[-1].name == "mmap":
                    payload_start = hex(int(syscalls[-1].ret, 16) + self.block_size)
                    self.mmaps[syscalls[-1].ret] = f"<mapped-addr{self.mmaps_count}>"
                    self.mmaps[
                        payload_start
                    ] = f"<mapped-addr{self.mmaps_count}> + {hex(self.block_size)}"
                    self.mmaps_count += 1
                syscalls[-1].prettify(self.heap_start, self.mmaps)

            self.line_index += 1

        try:
            libcall = Call(libcall_start, libcall_end)
        except UnfinishedCall:
            return None

        libcall.prettify(self.heap_start, self.mmaps)
        libcall.add_nested_calls(syscalls)

        return libcall

    def parse(self):
        libcalls = []
        libcall = self.parse_libcall()
        while libcall:
            libcalls.append(libcall)
            libcall = self.parse_libcall()

        output = "\n".join([str(libcall) for libcall in libcalls])
        output = "\n".join(
            [
                line.split("=")[0].ljust(90) + line[line.find("=") :]
                for line in output.splitlines()
            ]
            + self.exit_status
        )

        return self.program_output, output

@dataclasses.dataclass
class TestFile:
    executable: str
    out_file: str
    ref_file: str

class Test:
    SRC_PATH = os.path.join(os.path.dirname(os.path.realpath(__file__)), "../src")
    SNIPPET_DIR = os.path.join(os.path.dirname(os.path.realpath(__file__)), "snippets")
    REF_DIR = os.path.join(os.path.dirname(os.path.realpath(__file__)), "ref")

    def __init__(self, name, points) -> None:
        if "snippets/" in name:
            name = os.path.basename(name)

        self.name = name
        self.points = points
        self.test_file = TestFile(executable = os.path.join(Test.SNIPPET_DIR, self.name),
                out_file = os.path.join(Test.SNIPPET_DIR, self.name + ".out"),
                ref_file = os.path.join(Test.REF_DIR, self.name + ".ref"))
        self.output = None
        self.program_output = None

        self.env = os.environ.copy()
        self.env["LD_LIBRARY_PATH"] = os.environ.get("SRC_PATH", Test.SRC_PATH)

        print(self.name.ljust(33) + 24 * ".", end="")

    def run(self):
        if not os.path.isfile(self.test_file.executable):
            print(f"Failed to open {self.test_file.executable}", file=sys.stderr)
            sys.exit(-1)

        with Popen(
            [
                "ltrace",
                "-F",
                ".ltrace.conf",
                "-S",
                "-n",
                "2",
                "-x",
                "os_*",
                self.test_file.executable,
            ],
            stdout=PIPE,
            stderr=PIPE,
            env=self.env,
        ) as proc:
            stdout, stderr = proc.communicate()
            program_output = stdout.decode("ascii")
            ltrace_output = stderr.decode("ascii")
            self.program_output, self.output = LtraceParser(
                program_output, ltrace_output
            ).parse()
            self.output += "\n"

    def grade(self, verbose: bool, diff: bool, memcheck: bool) -> int:
        if not verbose and not diff and not memcheck:
            memcheck = True

        debug_msg = " debug"
        pass_msg = f" passed ...   {self.points}"
        fail_msg = " failed ...   0"

        diff_err = ""
        memcheck_err = ""

        if memcheck:
            diff = True
            memcheck_err = self.memcheck()
        if diff:
            verbose = False
            diff_err = self.diffcheck()
        if verbose:
            print(debug_msg, file=sys.stderr)
            print(self.output, file=sys.stderr)
            print("\n" + self.program_output, file=sys.stderr)
            return 0

        result = not diff_err and not memcheck_err
        print(pass_msg if result else fail_msg)

        if diff_err:
            if len(diff_err) > 20:
                diff_err = diff_err[:20] + ["[...]"]
            print(*diff_err[:3], sep="\n", file=sys.stderr)
            print(*diff_err[3:], sep="", file=sys.stderr)
        if memcheck_err:
            print(memcheck_err)

        return result

    def memcheck(self):
        if not os.path.isfile(self.test_file.executable):
            print(f"Failed to open {self.test_file.executable}", file=sys.stderr)
            sys.exit(-1)

        with Popen(
            [
                "valgrind",
                "--leak-check=full",
                "--track-origins=yes",
                self.test_file.executable,
            ],
            stdout=PIPE,
            stderr=PIPE,
            env=self.env,
        ) as proc:
            _, stderr = proc.communicate()
            valgrind_output = stderr.decode("ascii")

            if (
                "definitely lost" in valgrind_output
                or "indirectly lost" in valgrind_output
            ):
                return valgrind_output

            return []

    def diffcheck(self) -> bool:
        diffs = None

        if not os.path.isfile(self.test_file.ref_file):
            print(f"Failed to open {self.test_file.ref_file}", file=sys.stderr)
            sys.exit(-1)

        with open(self.test_file.out_file, "w", encoding="ascii") as fout:
            fout.write(self.output)

        with open(self.test_file.out_file, "r", encoding="ascii") as fout, open(
            self.test_file.ref_file, "r", encoding="ascii"
        ) as fref:
            diffs = list(
                difflib.unified_diff(
                    fout.readlines(),
                    fref.readlines(),
                    fromfile=self.test_file.out_file,
                    tofile=self.test_file.ref_file,
                    lineterm="",
                )
            )

        return diffs


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "test",
        nargs="?",
        default=None,
        help="Path to the test to run. If not specified, all tests are run.",
    )
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="Display test output."
    )
    parser.add_argument(
        "-d",
        "--diff",
        action="store_true",
        help="Show diff for failed tests. Disables verbose.",
    )
    parser.add_argument(
        "-m",
        "--memcheck",
        action="store_true",
        help="Check for memory leaks. Enables diff.",
    )

    args = parser.parse_args()

    return args.test, args.verbose, args.diff, args.memcheck


def main():
    total = 0
    test_name, verbose, diff, memcheck = parse_args()

    if test_name:
        test = Test(test_name, 1)
        test.run()
        test.grade(verbose, diff, memcheck)
        return

    for test_name, score in TESTS.items():
        test = Test(test_name, score)
        test.run()
        if test.grade(verbose, diff, memcheck):
            total += score

    print("\nTotal:" + " " * 59 + f" {total}/100")


if __name__ == "__main__":
    main()
