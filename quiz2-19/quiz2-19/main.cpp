//
//  main.cpp
//  quiz2-19
//
//  Created by 王英鉴 on 2019/9/30.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    for (int i = 0; i < 3; i++) {
        fork();
        wait(NULL);
        cout << "PID: " << getpid()<<endl ;
        
    }
    /*for (int i = 0; i < 3; i++) {
        fork();
        wait(NULL);
        cout << "PID: " << getpid()<<endl ;
    }*/
}
