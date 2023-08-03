# TLS Synchronization

## Question Text

Is placing `var` from `support/race-condition/c/race_condition_tls.c` in the TLS a valid form of synchronization?

## Question Answers

- No, because the race condition remains.
It just doesn't manifest itself anymore

+ No, because the threads now access different variables, not the same one

- Yes, because we now remove the race condition

- Yes, because now the result is correct

## Feedback

Synchronization means that both threads should access the same variable, whereas placing it in the TLS makes each of them access a copy of the variable.
