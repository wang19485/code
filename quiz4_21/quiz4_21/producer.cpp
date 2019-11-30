#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include "KernelSemaphore.h"
using namespace std;

int main() {
    cout << "This program will create the semaphore, initialize it to 0, ";
    cout << "then produce some data and finally V() the semaphore" << endl;
    KernelSemaphore ks("/my_kernel_sema", 0);
    sleep(rand() % 10);
    ks.V();
}
