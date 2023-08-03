---

## App Classification

---

### App Components

- Threads and processes
- Processes may be colocated on the same system
- Processes may be distributed on multiple systems

----

### App Components

![App Components](./media/app-components.svg)

---

### App Classification

- Single-process single-threaded
- Multi-threaded
- Multi-process
- Multi-system
- These apps use OS primitives to communicate between components (threads, processes)

----

### Single-process Single-threaded

- No actual software component interaction
- Simple applications that don't rely on complex features
- `ldd <exec> | grep pthread`

- `/bin/bash`, `/bin/dd`

----

### Single-process Multi-threaded Homogeneous

- Multiple threads doing the same work
- Threading models: boss-workers, worker threads, thread pools
- Generally little interaction: join at the end

- multi-threaded web servers
- `libx264` library for `ffmpeg`
- Firefox web browser: browser tabs

----

### Single-process Multi-threaded Heterogeneous

- Multiple threads, each doing different work

- Firefox web browser: browser management processes

----

### Multi-process Homogeneous

- Multiple processes doing the same work
- Process pool
- Generally no interaction: pre-fork, get job, serve

- Multi-process web servers (Apache2 mpm-prefork)
- Google Chrome: a process per Tab

----

### Multi-process Heterogeneous

- Multiple processes doing different items
- IPC mechanisms (pipes, message queues, sockets) to interface between processes

- Postfix
- GitLab

----

### Postfix

![Postfix](./media/postfix-architecture.svg) ([source](https://commons.wikimedia.org/wiki/File:Postfix_architecture.svg))

----

### GitLab

<img src="./media/gitlab-architecture.png" width="400" /> ([source](https://docs.gitlab.com/ee/development/architecture.html))

----

### Multi-system

- Processes run on different systems
- Used in distributed systems, data centers, computing clusters
- Typically a combination of homogeneous and heterogeneous systems and processes

- Kubernetes, OpenStack, Netflix backend servers

----

### Kubernetes

![Kubernetes Architecture](./media/kubernetes-architecture.png) ([source](https://medium.com/devops-mojo/kubernetes-architecture-overview-introduction-to-k8s-architecture-and-understanding-k8s-cluster-components-90e11eb34ccd))
