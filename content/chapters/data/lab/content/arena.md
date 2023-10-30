# Arena

Challenge tasks

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

**Note: the difference between initialization and assignment is that the initialization occurs when an object is being declared and occurs a single time (`Obj o1 = 1`), whereas assignement is decoupled from the declaration site and may occur multiple times (provided that the variable is mutable).**

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
