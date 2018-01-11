
#pragma once

#include <vector>
#include <deque>
#include <cstdio>
#include <string>
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
    void createNewProcess(int argc, char** argv);
    void loadCfg();
    void loadCfg(FILE* fp);
    void saveCfg(FILE* fp);
    const char* getUserName();
    bool checkAndAddCfg(const char* command);
    void removeFirstInCfg();

    pid_t my_pid;
    std::deque<Job> job_queue;
    
};