# Socket Test Case

Use `make` to compile the HTTP request reply once server.

```console
student@os:/.../test/c$ make
```

Start server then use an HTTP client (such as `wget`) to request a resource and then receive a reply.
You may also use a GUI browser.
The server URL should be <http://localhost:28282>.

```console
student@os:/.../test/c # on one console
student@os:/.../test/c$ ./http_reply_once

student@os:/.../test/c # on the second console
student@os:/.../test/c$ wget http://localhost:28282
```
