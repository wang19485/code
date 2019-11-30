#include <iostream>
#include <unistd.h>
#include <csignal>
#include <sys/time.h>
using namespace std;

void signal_handler (int signo) {
    cout << "Got SIGUSER1" << endl;
}
int main() {
    srand(time_t(NULL));
    struct timeval start, end;
    gettimeofday (&start, 0);
    //signal(SIGUSR1, signal_handler);
    int pid = fork();
    if (pid == 0) {
        for (int i = 0; i < 5; i++) {
            kill(getppid(), SIGUSR1);
            sleep(1);
        }
    }else{
        wait(0);
        gettimeofday(&end, NULL);
        int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
        int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
        cout << "Took " << secs << " seconds and " << usecs << " micor seconds" << endl;
    }
}
