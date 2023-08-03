---

## Thread-safety and Reentrancy

---

### Thread-safety and Reentrancy

* **Thread-safe function:** called simultaneously from multiple threads without race conditions
* **Reentrant function:** preempted at any time and re-called from the same thread with the same effects
  * Different from recursion:

![Recursion vs reentrancy](./media/recursive-vs-reentrant.svg)

----

#### Thread-safety and Reentrancy - Examples

```c [1 - 8 | 10 - 16 | 18 - 24 | 26 - 30]
/* Not thread-safe, not reentrant: */
int tmp
int add2(int x)
{
    tmp = x;
    /* Preempt here */
    return tmp + 2;
}

/* Reentrant, not thread-safe: */
int tmp
int add2(int x)
{
    tmp = x;
    return x + 2;
}

/* Thread-safe not reentrant: */
thread_local int tmp
int add2(int x)
{
    tmp = x;
    return tmp + 2;
}

/* Both thread-safe and reentrant: */
int add2(int x)
{
    return x + 2;
}
```
