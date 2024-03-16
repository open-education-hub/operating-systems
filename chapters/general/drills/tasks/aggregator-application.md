# Aggregator Application

## Scenario

We are pursuing the design of an aggregator application that interfaces with multiple sites / solutions of Large Language Models (LLMs) like ChatGPT.
The application should be portable across different architectures, operating systems, and interfaces: native, web, mobile.
The application will receive a query from the user, which it will then transmit to all LLM sites / solutions.
Then it will display all their responses, allowing the user to choose a response (from an LLM solution), possibly based on similarity to other responses from other LLM solutions.

Respond to the following questions with "True" or "False" and provide reasoning.
The justification should be simple, 2-3 sentences for each response.

## Questions

1. The aggregator application can be written in the C language.
Answer: True

1. Interaction with LLM sites can be done through named pipes mechanisms.
Answer: False

1. Two instances of the aggregator application can run on the same system.
Answer: True

1. The aggregator application is CPU intensive.
Answer: False

1. The aggregator application would benefit from increasing the file descriptor table size beyond the standard limit of 1024.
Answer: False / True, depending on argumentation

1. In the case of a multi-threaded implementation, the aggregator application would achieve significant performance improvements.
Answer: False

1. The aggregator application can run in a Docker container.
Answer: True

1. The protocol used for communication between the aggregator application and LLM sites must be HTTP.
Answer: False

1. The aggregator application can run as an unprivileged user.
Answer: True

1. The aggregator application's page table DOES NOT contain pages without write permission.
Answer: False

1. The system can only function if the communication between the aggregator application and LLM sites is encrypted.
Answer: False
