#include "submit.hpp"
#include <iostream>
#include <sys/file.h>  
#include <sys/types.h>
#include <pwd.h>

using namespace std;


Submit::Submit() {
    my_pid = getpid();
}

Submit::~Submit() {
    
}

void Submit::sub(int argc, char** argv) {
    
}

void Submit::show() {
    getCfg();
    for (auto p : job_queue) {
        cout << p.pid << "\t\t\t" << p.name << "\t\t" << p.user << endl;
    }
}

void Submit::getCfg() {
    fp = fopen("/tmp/submit_jobqueue", "r+");
    flock(fp->_fileno, LOCK_EX);
    job_queue.clear();

    char cmd[256]; 
    char user[64];
    pid_t pid;
    while (scanf("%d %s %s", &pid, cmd, user)) {
        Job job{pid, string(cmd), string(user)};
        job_queue.push_back(job);
    }

    flock(fp->_fileno, LOCK_UN); //释放文件锁  
    fclose(fp);
}

void Submit::saveCfg() {
    fp = fopen("/tmp/submit_jobqueue", "r+");
    flock(fp->_fileno, LOCK_EX);
    job_queue.clear();

    char cmd[256]; 
    char user[64];
    pid_t pid;
    while (scanf("%d %s %s", &pid, cmd, user)) {
        Job job{pid, string(cmd), string(user)};
        job_queue.push_back(job);
    }

    flock(fp->_fileno, LOCK_UN); //释放文件锁  
    fclose(fp);
}

const char* Submit::getUserName()
{
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    if (pw) return pw->pw_name;
    return "";
}