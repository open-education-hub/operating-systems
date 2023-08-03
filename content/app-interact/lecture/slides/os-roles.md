---

## Roles of the Operating System

---

### Reminder: Requirements

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

---

## OS Roles

- Operating system mediates app interaction
- Operating system provides primitives / mechanisms for app interaction
- Roles
  - registry: identifying app endpoints
  - post office: reliably passing messages between applications
  - police: ensuring access control and security
  - doorbell: app notification of incoming messages

----

## OS - The Lawmaker

- The OS is like a lawmaker the dictates how the interaction takes place
- Allows or denies the sending of data / notifications
- Ensures correct delivery of data / notification

----

## OS - The Lawmaker

![Multiple Apps Interacting through the OS](./media/multiple-apps-interaction.svg)
