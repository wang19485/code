#ifndef KernelSemaphore_h
#define KernelSemaphore_h

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
using namespace std;

class KernelSemaphore{
    string name;
    sem_t *sem;
public:
    KernelSemaphore (string _name, int _init_value){
        const char *namechar = name.c_str();
        if ((sem = sem_open(namechar, O_CREAT,0644,_init_value))== SEM_FAILED) {
            perror("sem_open");
        }
    }
    void P(){
        sem_wait(sem);
    }
    void V(){
        sem_post(sem);
    }
    ~KernelSemaphore (){
        sem_close(sem);
        const char *namechar = name.c_str();
        sem_unlink(namechar);
    }
};

#endif /* KernelSemaphore_h */
