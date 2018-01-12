Submit
=================

Submit is a small tool for linux multi-user task queue. It can run tasks until the task queue is empty. 

Now, it has following features:

* submit a task - it will automatically run at the queue is empty
* show queue - to check who is running jobs

You can use `-h` to check the helping message:

```
Submit v0.2.0
Usage:  sub [options] executable [args...]

        --show / -s                     Show task queue
        --help / -h / -?                Pring help message
```

