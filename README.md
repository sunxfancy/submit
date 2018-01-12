Submit
=================

Submit is a small tool for linux multi-user task queue. It can run tasks until the task queue is empty. 

Now, it has following features:

* submit a task - it will automatically run when the queue is empty
* show queue - to check who is running jobs

You can use `-h` to check the helping message:

```
Submit v0.2.0
Usage:  sub [options] executable [args...]

        --show / -s                     Show task queue
        --help / -h / -?                Pring help message
```

## Build And Test

To build the project, you need cmake, ninja-build, conan and codefactory

For ubuntu user, there are some tips:
```
sudo apt-get install cmake ninja-build python3-pip
pip3 install conan codefactory --user --upgrade
```

To build the release version, just run:
```
codef build -r
```
