# Setting up the Lab Environment

If you have already cloned the repository, make sure it is updated:

```console
student@os:~$ cd operating-systems

student@os:~/operating-systems$ git pull --rebase
```

The command may fail if you have uncommitted changes.
If that is the case, stash your changes, retry, and pop the stash:

```console
student@os:~/operating-systems$ git stash

student@os:~/operating-systems$ git pull --rebase

student@os:~/operating-systems$ git stash pop
```

If you haven't already cloned the repository, do so and then enter the repository:

```console
student@os:~$ git clone https://github.com/open-education-hub/operating-systems

student@os:~$ cd operating-systems
```

Navigate to a chapter's lab directory:

```console
student@os:~/operating-systems$ cd content/chapters/<chapter-name>/lab/
```

The possible options are: `software-stack`, `data`, `compute`, `io` and `app-interact`.

If you're using the OS-runner Docker container, you can use the following shortcuts:

`go-ss`       - changes directory to Software Stack lab

`go-data`     - changes directory to Data lab

`go-compute`  - changes directory to Compute lab

`go-io`       - changes directory to IO lab

`go-appInt`   - changes directory to App Interaction lab
