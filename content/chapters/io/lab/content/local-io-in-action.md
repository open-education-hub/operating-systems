# Local I/O in Action

Most of the time, file handling is a simple operation from the perspective of the application.
We've already looked at the [Deluge](https://www.deluge-torrent.org/) Bittorrent client written during the Data lab.
We'll examine it once more, but this time from the perspective of its I/O operations.
Being a Bittorrent client, we expect it to deal with I/O in 4 ways.
There are 2 "local" types of operations:

- reading local files from the disk to be sent to other clients

- writing the previously downloaded files to the disk

Simple, right?
Now we'll only look at the "local" part: reading and writing data to/from the disk.
The remaining 2 actions are about network-related operations.

- requesting files from other stations on the Web.
Those files are then retained in Deluge's memory while they're being downloaded

- sending (parts of) files to other clients.
Those files are first read from the disk, retained in memory for a while, and then sent over the internet.

Networking is complementary to local I/O and we'll discuss it starting from a [future section](./remote-io.md).

## Local I/O in Deluge

If you haven't done so in the Data lab, clone the [Deluge repository](https://github.com/deluge-torrent/deluge).

### Writing Data to Files

Now find the `write_torrentfile()` function in the repository.

It defines an inner function called `write_file()`, which does the actual writing.
Notice that it's very similar to the example we saw in `support/simple-file-operations/file_operations.py`:

```Python
with open(filepath, 'wb') as save_file:
    save_file.write(filedump)
```

The code above is the same as:

```Python
save_file = open(filepath, 'wb')
save_file.write(filedump)
save_file.close()
```

The `with` keyword is just a _context manager_ that makes sure `save_file` is also closed when its "body" finished.
Writing the data is done simply by calling the `write()` function.
As you've probably figured out, there's an entire **software stack** beneath this `write()` function that sends the data first to libc and then to the kernel.
Furthermore, the kernel itself has its own separate stack for handling I/O requests.

![Software Stacks Everywhere](../media/software-stacks-everywhere.jpeg)

### Error Handling

What is noteworthy about this short snippet is the (slightly) bigger picture - the error handling:

```Python
try:
    with open(filepath, 'wb') as save_file:
        save_file.write(filedump)
except OSError as ex:
    log.error('Unable to save torrent file to: %s', ex)
```

This is similar to the [`DIE()` macro](https://github.com/open-education-hub/operating-systems/blob/6c5082600239e5a6bfcb612f41986cf2660323bb/content/common/utils/utils.h#L23-L30) you have seen **(and used, right?)** throughout the labs, but less brutal.
While the `DIE()` macro kills the program upon encountering an error, Deluge's `try - except` approach simply logs an error and continues.
As you might imagine, there is no silver bullet when it comes to error handling.
What is important is that errors are somehow accounted for and not ignored.

This is especially true for I/O-related errors.
Because I/O handling means dealing with peripherals or devices outside the typical CPU-RAM interaction.
The more devices, the higher the complexity.
The higher the complexity, the higher the likelihood of errors.

[Quiz](../quiz/local-io-errors.md)

### Reading Data from Files

Now find the `load_resume_data_file()` function in the Deluge source code.
It is used when (re)starting to seed existing files to peers.

The function looks through all possible copies and backups of the file and loads them to a "torrent" format given by [`libtorrent`](https://www.libtorrent.org/).
For this, it calls `lt.bdecode()`.

As before, error handling is important:

```Python
try:
    with open(_filepath, 'rb') as _file:
        resume_data = lt.bdecode(_file.read())
except (OSError, EOFError, RuntimeError) as ex:
    if self.torrents:
        log.warning('Unable to load %s: %s', _filepath, ex)
    resume_data = None
```

So now we know how Deluge handles local files.
But we still don't know how it gets those files from peers.
We'll find out how in the following sections.
