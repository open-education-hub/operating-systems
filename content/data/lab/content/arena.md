# Arena

Go through the practice items below to hone your skills in working with data and memory.

## Page Mapper

Navigate to the `support/page-mapper/` directory.

Your goal is to update the `src/page_mapper.c` source code file to reserve virtual pages in the address space of the current process.
Use `mmap()` to reserve virtual pages.
Use anonymous mapping (i.e. the `MAP_ANONYMOUS`) flag.
Use any permissions required.

Inside the `src/` directory, use `make` to do a quick check of the implementation.
To test it, enter the `tests/` directory and run:

```console
make check
```

In case of a correct solution, you will get an output such as:

```text
./run_all_tests.sh
test_res_1                       ........................ passed ...  25
test_res_2                       ........................ passed ...  25
test_res_10                      ........................ passed ...  25
test_res_10_res_20               ........................ passed ...  25

Total:                                                           100/100
```

## Shellcode Executor

Navigate to the `support/exec-shellcode/` directory.

Your goal is to update the `src/exec-shellcode.s` source code file to be able to read and execute shellcodes from a given binary files.
The program thus acts as a shellcode tester.

A [shellcode](https://cocomelonc.github.io/tutorial/2021/10/09/linux-shellcoding-1.html) is a small program that is commonly used in memory-related security exploits as a form of arbitrary code execution.
It's a binary string consisting of instructions / code to be directly interpreted by the CPU during the execution of the targeted vulnerable program.

Shellcodes end up in an `exit()` system call to ensure a graceful exit of the program after running the shellcode.
Use `mmap()` to reserve a virtual page.
Use anonymous mapping (i.e. the `MAP_ANONYMOUS`) flag.
Use the proper permissions required to enable the shellcode to be read from the file into memory and then executed.

To test the implementation, enter the `tests/` directory and run:

```console
make check
```

As an extra item, add a shellcode for the `brk()` system call in the `tests/brk.asm` file.
It should be a simple shellcode that calls `brk(NULL)`, i.e. with the purpose of getting the current program break.

In case of a correct solution, you will get an output such as:

```text
./run_all_tests.sh
test_helloworld                  ........................ passed ...  25
test_getpid                      ........................ passed ...  25
test_openfile                    ........................ passed ...  25
test_brk                         ........................ passed ...  25

Total:                                                           100/100
```

## Access Counter

Navigate to the `support/access-counter/` directory.

Your goal is to update the `src/access_counter.c` source code file to capture memory access exceptions (i.e. the `SIGSEGV` signal) and to update page permissions in order for the access to eventually succeed.
Use `mprotect` to update the protection of the pages in stages: read, write and then exec.
Each time an update is made, the `counter` variable is increased;
this is used for testing.

The signal handler is already in place as the `access_handler()` function.
It is called any time a `SIGSEGV` signal is being sent out to the current process.
You will update the handler by following the `TODO` comments and instructions here.

The `pages` array stores information about accessed pages.
Assume the `MAX_PAGES` size of the array is enough to store information.
When an existing page is accessed and causes a memory exception, the permission is update, in the stages mentioned above: read, write, and then exec.
When a new page is accessed, a new entry is filled in the `pages` array, initialized with read protection.
Use `mmap()` to reserve virtual pages.
Use anonymous mapping (i.e. the `MAP_ANONYMOUS`) flag.
Use any permissions required.

To test it, enter the `tests/` directory and run:

```console
make check
```

In case of a correct solution, you will get an output such as:

```text
./run_all_tests.sh
test_acess_read                  ........................ passed ...   9
test_acess_write                 ........................ passed ...   9
test_acess_exec                  ........................ passed ...  10
test_acess_read_write            ........................ passed ...  12
test_acess_read_exec             ........................ passed ...  12
test_acess_write_exec            ........................ passed ...  12
test_acess_exec_read             ........................ passed ...  12
test_acess_exec_write            ........................ passed ...  12
test_acess_write_read            ........................ passed ...  12

Total:                                                           100/100
```

## Memory Support

**Manual memory management** (MMM) is one of the most difficult tasks.
Even experienced programmers make mistakes when tackling such a complicated endeavor.
As a consequence, the programming world has been migrating towards languages that offer automatic memory management (AMM).
AMM programming languages typically offer a garbage collector that tracks down the usage of objects and frees memory once no references exist to a given object.
As a consequence, garbage collected programming languages are easier to use and safer.
However, this comes with a cost: the garbage collector, in most cases, requires a significant amount of resources to run.
Therefore, for performance-critical systems, MMM is still the preferred solution.

A middle-ground between programming languages that have AMM (Java, Python, Swift, D) and those that do not (C, C++) is represented by those languages that do not have built-in AMM but offer the possibility to implement it as a library solution (C++, D).
Concretely, these languages offer lightweight library solutions to optimally track down the lifetime of an object.
This is done by using reference counted objects.

### Reference Counting

Reference counting is a technique of tracking the lifetime of an object by counting how many references to an object exist.
As long as at least one reference exists, the object cannot be destroyed.
Once no reference to a given object exists, it can be safely destroyed.
Reference counted is typically implemented by storing a count with the actual payload of the object.
Every time a new reference to the object is created, the reference count is incremented.
Every time a reference expires, the reference is decremented.

The operations that trigger a reference increment are:

- initializing an object from another object.
- assigning an object to another object.

The operations that trigger a reference decrement are:

- the lifetime of an object expires

Modern programming languages offer the possibility to specify what code should be run in each of these situations, therefore enabling the implementation of referenced counted data structures.
As such, copy constructors may be used to automatically initialize an object from another object, assignment operators may be used to assign an object to another object and destructors may be used to destroy objects.

### Operator overloading

Navigate to the `support/reference-counting` directory.
Analyze the `operators.d` file.
A `struct` is defined that also implements 4 special functions: a constructor, a copy constructor, an assignment operator and a destructor.
Each of these special functions may be called automatically by the compiler:

- the constructor is called automatically whenever an object is initialized with a field of a type that corresponds to the constructor parameter type.
- the copy constructor is called automatically when an object is initialized from an object of the same type.
- the assignment operator is called automatically when an object is assigned an object of the same type.
- the destructor is called automatically whenever an object goes out of scope.

**Note: the difference between initialization and assignment is that the initialization occurs when an object is being declared and occurs a single time (`Obj o1 = 1`), whereas assignment is decoupled from the declaration site and may occur multiple times (provided that the variable is mutable).**

Compile and run the program in `operators.d`.
Notice how the different special functions are automatically called.
Considering the definition of `Obj` from the file `operators.d`, answer the following [Quiz](../quiz/operators.md).

#### Practice

Navigate to the `support/reference-counting` directory.
Analyze the `refcount_skel.d`.
A reference counted `int` array is implemented, however, some bits are missing.
Run the code, try to understand what happens.

The constructor allocates memory for the array, whereas the destructor deallocates it.
Compile and run the code.
Notice how the array's memory  is automatically managed.

1. Uncomment the following line in the `main` function (`//test1()`).
   Run the code.
   What happens?
   Why?

1. The reference counted array does not implement the copy constructor.
   Comment the `version(none)` annotation for the copy constructor and implement the logic so that the reference counted array is correct.
   When an object is initialized from another object, we need to appropriately set the fields and then increment the reference count.
   Once you have completed this exercise, make sure the output is correct and that the reference counted array is not freed too early.

1. Uncomment the following line in the `main` function (`//test2()`).
   Run the code.
   What happens?
   Why?
   Use GDB to find out.

1. The reference counted array does not implement the assignment operator.
   Comment the `version(none)` annotation for the assignment operator and implement the logic so that the reference counted array is correct.
   When an object is assigned to another object, we need to first decrement the count for the object that is being assigned to, then fill the fields similarly to the copy constructor case and lastly increment the count for the assigned object.
   After completing the exercise, make sure that the memory is properly managed.

1. Play with your reference counted array and create different scenarios to test its limits.
