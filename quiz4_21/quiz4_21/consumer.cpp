#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include "KernelSemaphore.h"
using namespace std;

int main() {
    KernelSemaphore ks("my_kernel_sema", 0);
    ks.P();
    cout << "I can tell the producer is done" << endl;
}
