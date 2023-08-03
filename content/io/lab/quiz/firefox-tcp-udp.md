# Firefox: TCP or UDP?

## Question Text

If the user requests a text-based web page (such as [our Operating Systems course](https://open-education-hub.github.io/operating-systems/)), should the browser transfer the content using TCP or UDP?
What about video content, such as YouTube?

## Question Answers

+ TCP and UDP, respectively

- UDP and TCP, respectively

- both connections should use TCP

- both connections should use UDP

## Feedback

The "TCP vs UDP" question boils down to 2 things:

- is the data updated in real-time (multiple times per second)?
- can we afford a few errors / missing messages?

If the answers to both questions is "Yes", then we should use UDP.
If they're "No", we should use TCP.
However, if the answer to one question is "Yes" and the other one is "No", then it gets complicated.

Luckily, in our cases, the answers are quite clear.
We don't update text-based content too often and since it needs to be precise, handling broken packets is important.
On the other hand, a streaming-based site, such as YouTube sends data in real time and thus a few errors here and there can be omitted.
So <https://open-education-hub.github.io/operating-systems> is going to be served via TCP, while YouTube videos via UDP.
