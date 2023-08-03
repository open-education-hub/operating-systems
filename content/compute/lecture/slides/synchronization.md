---

## Synchronization

---

#### Synchronization - Why?

* Each thread believes it's the only one running
* ... but this is not true
* Threads share resources:
  * RAM
  * files
  * networking
  * CPU

----

#### Synchronization - How?

* We want to give a thread **exclusive access** to a resource at a given time
* Other threads **wait** to receive access

----

#### Synchronization - Example

* `demo/race-condition/race_condition.c`
* `var++` equivalency (**critical section**):

![Race Condition - Instructions](./media/race-condition-generated.gif)

* In the end `var = 1` or `var = 2`

----

#### Synchronization Mistake - TOCTOU

```c
if (lock = 0) {
	lock = 1;
    /* critical section */
    lock = 0;
}
```

![Race Condition - TOCTOU](./media/race-condition-toctou-generated.gif)

* **Wrong:** threads enter critical section simultaneously

----

#### Synchronization - Solution

* Only allow **one thread** to access the critical section at a given time (mutual exclusion)

![Race Condition - Using a lock](./media/race-condition-lock-generated.gif)

* In the end `var` is **always** 2
* [Quiz](../quiz/not-race-condition.md)
