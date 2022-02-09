## Question Text

When is the major drawback of this allocation strategy?

## Question Answers

- Allocating memory upfront is wasteful because you do not use it right away.
+ After a few reallocations, you might be allocating too much memory upfront.
- The `appendElem` function becomes more complex.
- The `capacity` field requires extra space which may lead to memory exhaustion when using a large number of `IntArray`s

## Feedback

The reallocation factor is highly dependant on the use case. For applications that require a long time to use up the memory that they allocated it is better to use a linear function and not an exponential one.
