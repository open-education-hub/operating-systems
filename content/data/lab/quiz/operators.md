# Operator Overloading

## Question Text

How many constructor calls, copy constructor calls, assignment operator calls and destructor calls does the following program issue?

```d
Obj quiz(Obj o1, Obj o2)
{
    o2 = o1;
    return o2;
}
void main()
{
    Obj b = quiz(o1, o2);
}
```

## Question Answers

+ constructor calls = 0, copy constructor calls = 3, assignment operator calls = 1, destructor calls = 3

- constructor calls = 1, copy constructor calls = 2, assignment operator calls = 1, destructor calls = 2

- constructor calls = 0, copy constructor calls = 2, assignment operator calls = 1, destructor calls = 2

- constructor calls = 0, copy constructor calls = 3, assignment operator calls = 1, destructor calls = 1

## Feedback

- There are no constructor calls because there is no object construction when using `int`.

- There are 3 copy constructor calls: for passing `o1`, for passing `o2`, and for returning `o2`.

- There is 1 assignment operator call for `o2 = o1`.

- There are 3 destructor calls, because each constructed object needs to be destroyed.
