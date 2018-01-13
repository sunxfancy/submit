
#pragma once

#include <vector>
#include <deque>
#include <cstdio>
#include <string>
#include <unistd.h>

struct Job {
    Job(pid_t pid,std::string name,std::string user) {
        this->pid = pid;
        this->name = name;
        this->user = user;
    }

    Job(const Job& other) { 
        pid = other.pid;
        name = other.name;
        user = other.user;
    }

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

    bool checkAndAddCfg(const char* command);
    void removeFirstInCfg();
    void setupSignal();
    FILE* rfp;
private:
    void createNewProcess(int argc, char** argv);
    void loadCfg();
    void loadCfg(FILE* fp);
    void saveCfg(FILE* fp);
    const char* getUserName();
    

    pid_t my_pid;
    std::deque<Job> job_queue;
    
};