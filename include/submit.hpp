
#pragma once

#include <vector>
#include <string>
#include <cstdio>
#include <unistd.h>

struct Job {
    pid_t pid;
    std::string name;
    std::string user;
};

class Submit {
public:
    Submit();
    ~Submit();

    /** 
     * submit a job, if something is running, change the queue file and waiting it.
     */
    void sub(int argc, char** argv);

    /**
     * show the task queue
     */
    void show();

private:
    void getCfg();
    const char* getUserName();

    pid_t my_pid;
    std::vector<Job> job_queue;
    FILE* fp;
};