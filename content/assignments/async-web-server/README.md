# Asynchronous Web Server

## Objectives

- Deepening the concepts related to working with sockets.
- Developing skills in implementing and designing applications that use asynchronous operations and other advanced I/O operations.
- Deepening the use of the API for advanced I/O operations in the Linux operating system.

## Statement

Implement a web server that uses the following advanced I/O operations:

- Asynchronous operations on files
- Non-blocking operations on sockets
- Zero-copying
- Multiplexing I/O operations

The server implements a limited functionality of the HTTP protocol: passing files to clients.

The web server will use the multiplexing API to wait for connections from clients - [epoll](https://man7.org/linux/man-pages/man7/epoll.7.html).
On the established connections, requests from clients will be received and then responses will be distributed to them.


The server will serve files from the `AWS_DOCUMENT_ROOT` directory, defined within the assignments' [header](./skel/aws.h).
Files are only found in subdirectories `AWS_DOCUMENT_ROOT/static/` and `AWS_DOCUMENT_ROOT/dynamic/`.
The corresponding request paths will be, for example, `AWS_DOCUMENT_ROOT/static/test.dat` and `AWS_DOCUMENT_ROOT/dynamic/test.dat`.
The file processing will be:

- The files in the `AWS_DOCUMENT_ROOT/static/` directory are static files that will be transmitted to clients using the zero-copying API - [sendfile](https://man7.org/linux/man-pages/man2/sendfile.2.html)]
- Files in the `AWS_DOCUMENT_ROOT/dynamic/` directory are files that are supposed to require a server-side post-processing phase. These files will be read from disk using the asynchronous API and then pushed to the clients. Streaming will use non-blocking sockets (Linux)
- An [HTTP 404](https://en.wikipedia.org/wiki/HTTP_404) message will be sent for invalid request paths

After transmitting a file, according to the HTTP protocol, the connection is closed.

### Details and recommendations for the implementation

- Implementing the assignment requires having a state machine for each connection, which you periodically query and update as the transfer proceeds.
Check the `connection_state` data structure defined in the [assignment header](./skel/awh.h).
- Find the `connection` data structure defined in the [assignment header](./skel/awh.h).
This can be used to keep track of an open connection.
- Definitions of other useful macros and data structures can be found in the assignment header.
- HTTP responses will have the code `200` for existing files and `404` for not existing files.
    - A valid response consists of the HTTP header, containing the related directives, two newlines (`\r\n\r\n`), followed by the actual content (the file).
    - Sample answers can be found in the parser test file or in the provided sample.
    - You can use predefined request directives such as `Date`, `Last-Modified`, etc.
        - The `Content-Length` directive **must** specify the size of the HTTP content (actual data) in bytes.
        - The `Connection` directive **must** be initialized to `close`.
- The port on which the web server listens for connections is defined within the assignment header: the `AWS_LISTEN_PORT` macro.
- The root directory relative to which the resources/files are searched is defined within the assignment header as the `AWS_DOCUMENT_ROOT` macro.

## Support Code

### HTTP Parser

The clients and server will communicate using the HTTP protocol.
For parsing HTTP requests from clients we recommend using [this HTTP parser](https://github.com/nodejs/http-parser), also available in the assignments' [http-parser](./skel/http-parser).
You will need to use a callback to get the path to the local resource requested by the client.
Find a simplified example of using the parser in the [samples directory](./skel/http-parser/samples/).

### API and Implementation Tasks

The [skel/aws.c](./skel/aws.c) file contains the code skelethon with several functions that have to be implemented.
Follow the `TODO` areas in the file to start your implementation.

> It can be reorganized as desired, as long as all the requirements of the assignment are implemented.

## Testing and Grading

The testing is automated.
Tests are located in the `tests/` directory.

To test your implementation, do the following steps:

- Run the `make` command inside the `skel/` directory and make sure it compiles with no errors and that the `aws` executable is generated.
- Run the `make check` command in the `tests/` directory.

There are 35 tests for this assignment, of which 13 are doubled by a memory leak check test.
A successful run looks as the following:

```
student@so:~/operating-systems/content/assignments/async-web-server/tests$ make check
make -C _test
make[1]: Entering directory '/home/student/operating-systems/content/assignments/async-web-server/tests/_test'
make[1]: Nothing to be done for 'all'.
make[1]: Leaving directory '/home/student/operating-systems/content/assignments/async-web-server/tests/_test'

                        = Testing - Asynchronous Web Server =

01) Test executable exists.............................................passed  [01/90]
02) Test executable runs...............................................passed  [01/90]
03) Test listening.....................................................passed  [01/90]
04) Test listening on port.............................................passed  [01/90]
05) Test accepts connections...........................................passed  [01/90]
06) Test accepts multiple connections..................................passed  [01/90]
07) Test epoll usage...................................................passed  [01/90]
08) Test disconnect....................................................passed  [01/90]
09) Test multiple disconnect...........................................passed  [01/90]
10) Test connect disconnect connect....................................passed  [01/90]
11) Test multiple connect disconnect connect...........................passed  [01/90]
12) Test unordered connect disconnect connect..........................passed  [01/90]
13) Test replies http request..........................................passed  [02/90]
13) Test replies http request - memcheck...............................passed  [01/90]
14) Test second replies http request...................................passed  [01/90]
15) Test sendfile usage................................................passed  [02/90]
16) Test small static file wget........................................passed  [02/90]
17) Test small static file wget cmp....................................passed  [04/90]
17) Test small static file wget cmp - memcheck.........................passed  [01/90]
18) Test large static file wget........................................passed  [02/90]
19) Test large static file wget cmp....................................passed  [04/90]
19) Test large static file wget cmp - memcheck.........................passed  [01/90]
20) Test bad static file 404...........................................passed  [02/90]
21) Test bad path 404..................................................passed  [02/90]
22) Test get one static file then another..............................passed  [02/90]
22) Test get one static file then another - memcheck...................passed  [01/90]
23) Test get two simultaneous static files.............................passed  [03/90]
23) Test get two simultaneous static files - memcheck..................passed  [01/90]
24) Test get multiple simultaneous static files........................passed  [04/90]
24) Test get multiple simultaneous static files - memcheck.............passed  [01/90]
25) Test io submit uses................................................passed  [02/90]
26) Test small dynamic file wget.......................................passed  [02/90]
27) Test small dynamic file wget cmp...................................passed  [04/90]
27) Test small dynamic file wget cmp - memcheck........................passed  [01/90]
28) Test large dynamic file wget.......................................passed  [02/90]
29) Test large dynamic file wget cmp...................................passed  [04/90]
29) Test large dynamic file wget cmp - memcheck........................passed  [01/90]
30) Test bad dynamic file 404..........................................passed  [02/90]
31) Test get one dynamic file then another.............................passed  [03/90]
31) Test get one dynamic file then another - memcheck..................passed  [01/90]
32) Test get two simultaneous dynamic files............................passed  [04/90]
32) Test get two simultaneous dynamic files - memcheck.................passed  [01/90]
33) Test get multiple simultaneous dynamic files.......................passed  [05/90]
33) Test get multiple simultaneous dynamic files - memcheck............passed  [01/90]
34) Test get two simultaneous static and dynamic files.................passed  [03/90]
34) Test get two simultaneous static and dynamic files - memcheck......passed  [01/90]
35) Test get multiple simultaneous static and dynamic files............passed  [04/90]
35) Test get multiple simultaneous static and dynamic files - memcheck.passed  [01/90]

                                                                       Total:  [90/100]
```

Individual tests can be run using the `./run_test.sh` bash script as the following:

```
student@so:~/operating-systems/content/assignments/async-web-server/tests$ ./_test/run_test.sh 3
03) Test listening.....................................................passed  [01/90]

```

Where `3` is the test you want to run.

Some tests are doubled by a memory check test.
This will only run if the regular test passed.
For example, test 31 will output the following in case of success:

```
student@so:~/operating-systems/content/assignments/async-web-server/tests$ ./_test/run_test.sh 31
31) Test get one dynamic file then another.............................passed  [03/90]
31) Test get one dynamic file then another - memcheck..................passed  [01/90]
```

and one of the following in case of error:

```
# if the regular tests failed, the memory check tests is not performed
student@so:~/operating-systems/content/assignments/async-web-server/tests$ ./_test/run_test.sh 31
31) Test get one dynamic file then another.............................failed  [ 0/90]
31) Test get one dynamic file then another - memcheck..................passed  [01/90]
```

> Note: The memcheck test for failed regular tests will not be taken into consideration for the final score.
  This output will be fixed in the next commit.


Tests use the `static/` and `dynamic/` folders.
These folders are created and removed using the `init` and `cleanup` arguments to `_test/run_test.sh`.

### Behind the Scenes

Tests are basically unit tests.

Each test function follows the unit test patter: initialization, action,
evaluation.

Each test starts the server, creates a given context, checks for validity and
then terminates the server process.

### Debugging

Logs are collected in `test.log` and `wget.log` files.

## Resources

- [sendfile](https://man7.org/linux/man-pages/man2/sendfile.2.html)

- [io_setup & friends](https://man7.org/linux/man-pages/man2/io_setup.2.html)

- [epoll](https://man7.org/linux/man-pages/man7/epoll.7.html)
