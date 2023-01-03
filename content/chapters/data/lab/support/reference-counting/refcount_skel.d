// SPDX-License-Identifier: BSD-3-Clause

import core.stdc.stdlib : malloc, free;
import std.stdio : writeln, printf;

int instance_generator;

struct RefCountedIntArray
{
    int* ptr;
    int* refcount;
    int instance_no;

    size_t size;

    this(int[] a)
    {
        printf("Creating ref counted array (instance: %d) for: ", instance_generator);
        writeln(a);

        // allocate memory for array and refcount
        ptr = cast(int*)malloc(int.sizeof * a.length);
        refcount = cast(int*)malloc(int.sizeof);

        // initialize ref counted array
        foreach(i, elem; a)
            ptr[i] = elem;

        // initialize size and ref count
        size = a.length;
        *refcount = 1;

        instance_no = instance_generator;
        instance_generator++;
    }

    // copy constructor
    // `version(none)` functions are ignored.
    // uncomment when you want to implement this
    version(none)
    this(ref RefCountedIntArray src)
    {
        // TODO - fill in the fields and correctly update the ref count

    }

    // assignment operator
    version(none)
    void opAssign(ref RefCountedIntArray src)
    {
        // TODO
    }

    void printArray(ref RefCountedIntArray src)
    {
        printf("array: [");
        int i;
        for (i = 0; i < src.size-1; i++)
            printf("%d, ", src.ptr[i]);
        printf("%d]\n", src.ptr[i]);
    }

    // destructor
    ~this()
    {
        printf("Destroying instance %d\n", instance_no);
        (*refcount)--;
        if (*refcount == 0)
        {
            printf("Freeing ");
            printArray(this);
            free(ptr);
            free(refcount);
        }
    }
}

void doSomething(RefCountedIntArray arr)
{
    writeln("Doing some work");
}

RefCountedIntArray fun()
{
    RefCountedIntArray p = RefCountedIntArray([1, 2, 3]);
    RefCountedIntArray p2 = p;
    return p2;
}

void test1()
{
    writeln("==== 1 =====");
    RefCountedIntArray p = fun();
    writeln("==== 2 =====");
    // should print `1`
    writeln(p.ptr[0]);
}

RefCountedIntArray gun(RefCountedIntArray p1)
{
    RefCountedIntArray p2 = RefCountedIntArray([1, 1, 1]);
    p2 = p1;
    return p2;
}

void test2()
{
    writeln("==== 3 =====");
    RefCountedIntArray p = RefCountedIntArray([5, 5, 5]);
    RefCountedIntArray p2 = gun(p);
    p2 = p;
    writeln("==== 4 =====");
}

void main()
{
    RefCountedIntArray arr = RefCountedIntArray([1, 2, 6]);
    //test1();
    //test2();
}
