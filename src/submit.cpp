#include "submit.hpp"
#include <iostream>
#include <sys/file.h>  
#include <sys/types.h>
#include <pwd.h>
#include <chrono>
#include <thread>
#include <sys/wait.h>


using namespace std;


Submit::Submit() {
    my_pid = getpid();
}

Submit::~Submit() {
    
}

void Submit::sub(int argc, char** argv) {
    FILE* rfp = fopen("/tmp/submit_running.lock", "w+");
    if (flock(rfp->_fileno, LOCK_EX|LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
            // lock file was locked, something running
            if (checkAndAddCfg(argv[0])) {
                flock(rfp->_fileno, LOCK_EX); // first lock, means the next will be this one
                goto BEGIN_WORKING;
            } else {
                flock(rfp->_fileno, LOCK_EX);
                goto STILL_WAITING;
            }
        } else {
            // error
            printf("inner error\n");
        }
    } else {
        // flock(rfp->_fileno, LOCK_UN);
        // lock file was unlocked, nothing running or just switch programs
        if (checkAndAddCfg(argv[0])) {
            goto BEGIN_WORKING;
        } else {
            goto STILL_WAITING;
        }
    }

STILL_WAITING:
    loadCfg();
    if (job_queue.front().pid == my_pid) goto BEGIN_WORKING;
    flock(rfp->_fileno, LOCK_UN);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    flock(rfp->_fileno, LOCK_EX);
    goto STILL_WAITING;

BEGIN_WORKING:
    createNewProcess(argc,argv);
    // remove first line
    removeFirstInCfg();
    flock(rfp->_fileno, LOCK_UN); 
    fclose(rfp);
}

void Submit::createNewProcess(int argc, char** argv) {
    pid_t pid=fork();              //   父进程返回的pid是大于零的，而创建的子进程返回的pid是 等于0的，这个机制正好用来区分 父进程和子进程
    if(pid==0)//子进程
    {  
        execvp(argv[0], argv);
        exit(-1); //子进程加载异常，否则这句代码应该在加载后被覆盖
    }
    else      //父进程
    {      
        wait(NULL);   //等待子进程结束
        printf("\work complete\n");
    }
}


void Submit::show() {
    loadCfg();
    if (job_queue.empty()) {
        printf("Now, the job queue is empty.\n");
    }
    for (auto p : job_queue) {
        cout << p.pid << "\t\t\t" << p.name << "\t\t" << p.user << endl;
    }
}

void Submit::loadCfg() {
    FILE* fp = fopen("/tmp/submit_jobqueue.lock", "w+");　// open lock file, if not exist, then create one
    flock(fp->_fileno, LOCK_EX);  // lock

    FILE* frp = fopen("/tmp/submit_jobqueue", "r");
    if (frp != NULL) {
        loadCfg(frp);
        fclose(frp);
    }

    flock(fp->_fileno, LOCK_UN);  // unlock
    fclose(fp);  // release file
}

void Submit::loadCfg(FILE* fp) {
    job_queue.clear();

    char cmd[256]; 
    char user[64];
    pid_t pid;
    while (fscanf(fp, "%d %s %s", &pid, cmd, user) != EOF) {
        Job job{pid, string(cmd), string(user)};
        job_queue.push_back(job);
    }
}

void Submit::saveCfg(FILE* fp) {
    for (const Job& p : job_queue) {
        fprintf(fp, "%d %s %s\n", p.pid, p.name.c_str(), p.user.c_str());
    }
    fprintf(fp, "\n");
}

// return true means queue empty
bool Submit::checkAndAddCfg(const char* command) {
    bool ret;
    FILE* fp = fopen("/tmp/submit_jobqueue.lock", "w+");
    flock(fp->_fileno, LOCK_EX);
    
    FILE* frp = fopen("/tmp/submit_jobqueue", "r");
    if (frp != NULL) {
        loadCfg(frp);
        fclose(frp);
    }
    
    if (job_queue.empty()) ret = true; else ret = false;

    Job job{my_pid, string(command), string(getUserName())};
    job_queue.push_back(job);

    FILE* fwp = fopen("/tmp/submit_jobqueue", "w");
    saveCfg(fwp);
    fclose(fwp);

    flock(fp->_fileno, LOCK_UN); 
    fclose(fp);
    return ret;
}



void Submit::removeFirstInCfg() {
    FILE* fp = fopen("/tmp/submit_jobqueue.lock", "w+");
    flock(fp->_fileno, LOCK_EX);

    FILE* frp = fopen("/tmp/submit_jobqueue", "r");
    if (frp != NULL) {
        loadCfg(frp);
        fclose(frp);
    }
    
    if (!job_queue.empty())
        job_queue.pop_front();
    FILE* fwp = fopen("/tmp/submit_jobqueue", "w");
    saveCfg(fwp);
    fclose(fwp);

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