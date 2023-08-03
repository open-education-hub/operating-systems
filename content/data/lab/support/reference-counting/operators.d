// SPDX-License-Identifier: BSD-3-Clause

import std.stdio;
import core.stdc.stdlib;

struct Obj
{

    // constructor
    this(int a)
    {
        writeln("---calling constructor");
    }

    // copy constructor
    this(ref Obj obj)
    {
        writeln("---calling copy constructor");
    }

    // assignment operator
    void opAssign(ref Obj obj)
    {
        writeln("---calling assignment operator");
    }

    // destructor
    ~this()
    {
        writeln("---calling destructor");
    }
}

void fun(Obj o) {}

void main()
{
    writeln("constructor call");
    Obj o1 = 1;                     // => rewritten to `Obj o1 = Obj(1);`

    writeln("copy constructor call");
    Obj o2 = o1;                    // => rewritten to `Obj o2 = Obj(o1);`

    writeln("assignment operator call");
    o2 = o1;                        // => rewritten to `o2.opAssign(o1)`

    writeln("initializing a function parameter");
    fun(o2);                        // => rewritten to `fun(Obj(o2))`

    writeln("destroying created objects");
    // compiler inserts `o1.~this()` and `o2.~this()`
}
