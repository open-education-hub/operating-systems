# Valgrind Leaks

## Question Text

```c
struct student {
    char *name;
    int age;
}

struct student *s = malloc(sizeof(*s));
s->name = strdup("Reginald");
// ...
free(s);
```

What are the leaks in the above c program?

## Question Answers

- There are no leaks

- `s->name` is **definitely lost**

+ `s->name` is **indirectly lost**

- `s->name` is **still reachable**

## Feedback

`strdup()` allocates memory for a string so the returned pointer must be freed.
Freeing `s` will leave us unable to free `s->name`, so `s->name` is **indirectly lost**.
Find more about valgrind leak categories [here](https://valgrind.org/docs/manual/faq.html#faq.deflost).
