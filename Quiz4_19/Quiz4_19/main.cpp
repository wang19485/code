#include <iostream>
#include <unistd.h>
#include <csignal>
#include <sys/time.h>
using namespace std;

void signal_handler(int sig){
    int st = wait(0);
    cout << "pid: " << st << endl;
    cout << "Child exited succesfully" << endl;
}


int main() {
    int pid = fork();
    if (pid == 0) {
        cout << "I'm child, sleep 3 seconds" << endl;
        sleep(3);
        exit(0);
    }else{
        signal(SIGCHLD, signal_handler);
        while (true) {
            sleep(1);
            cout << "I'm parent" << endl;
        }
    }
}
