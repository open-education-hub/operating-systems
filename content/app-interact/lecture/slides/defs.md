---

## Definitions and Terms

---

- What does it mean that applications interact?
- Do the following programs interact with other applications?

---

### Exhibit 1

```c
#include <stdio.h>

int main(void)
{
	printf("Hello, world\n");
	return 0;
}
```

----

### Exhibit 1

- The program simply prints a message to the standard output.
- The terminal runs the program, so we do have some app interaction.
- Also, it can interact with other programs by doing: `./hello_world | grep Hello`
- Interaction is static.
- However, this is not a voluntary interaction on the part of the program.
- The program was designed as a standalone one.

----

### Exhibit 1 - Creating Interaction

- `demo/send-receive/reader.c`
- `demo/send-receive/writer.c`
- `demo/send-receive/send_receive_pipe.c`

---

### Exhibit 2

```c
// writer.c
int main(void)
{
	FILE *fp = fopen("myf.txt", "r");
	fprintf(fp, "Hello");
	fclose(fp);
	return 0;
}
```

```c
// reader.c
int main(void)
{
	char a[20];
	FILE *fp = fopen("myf.txt", "r");
	fscanf(fp, "%s", a);
	printf("%s\n", a);
	fclose(fp);
	return 0;
}
```

----

### Exhibit 2

- The 2 programs indeed interact.
- But is there any difference from the previous example?
- There is no protocol of interaction.
- If one of the applications did not exist, the other one could still be a valid, meaningful program.

----

### Exhibit 2

- What if we start the reader before the writer?

<!-- .element class="fragment" -->

- Synchronization is required.

<!-- .element class="fragment" -->

----

### App Interaction

- Communication (data transfer)

<!-- .element class="fragment" -->

- Synchronization (notification)

<!-- .element class="fragment" -->

---

### Exhibit 3

```c
int main(void)
{
	pid_t pid = fork();
	if (pid == 0) {
		sleep(2);
		exit(EXIT_SUCCESS);
	}

	waitpid(pid, &status, 0);

	return 0;
}
```

----

### Exhibit 3

- Synchronization, but no communication
- The programs interact in a structured manner.
- One process waits for the other to finish.
- Interaction is dynamic - e.g. a process actively waits for the other.
- The 2 processes have been designed to work together.

---

### Exhibit 4 - WhatsApp Application

![App1](./media/whatsApp.svg)

----

### Exhibit 4 - WhatsApp Application

- There is interaction between the main client application and other applications: photos, location, YouTube etc.
- There is also interaction with the web server when sending messages.

---

### App Interaction

- Applications that run at the same time and that communicate with each other during their lifetimes.
- This communication involves:
  - passing messages (**communication**)
  - sending / waiting for notifications (**synchronization**)

----

### Requirements for Interaction

- Address / Identity of processes
  - Process ID
  - Hostname, port
- Communication channel
  - Buffer to store data
  - "Endpoints" to send / receive data from buffer
- Address / Identity of channel
  - Path in filesystem
  - Hostname, port, path
  - ID

----

### Metrics and Goals for Interaction

- Speed: fast transfer
- Latency: time to actual delivery
- Reliability
- Intra-system interaction
  - Security: access control
- Inter-system interaction
  - Security: confidential connection
  - Scalability: multiple connections
