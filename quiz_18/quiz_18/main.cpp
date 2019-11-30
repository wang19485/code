#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main() {
    int pid = fork();
    char * arglist[] = {"ls",NULL};
    execvp("ls",arglist);
    cout << "searching..." << endl;
    string gg = "";
    cin >> gg;
}
