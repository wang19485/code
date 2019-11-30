#include <iostream>
#include <thread>
#include <stdlib.h>
#include "Semaphore.h"
#include <vector>
#include <unistd.h>
#include <queue>

using namespace std;

int buffer = 0;
Semaphore a_done(1);
Semaphore b_done(0);
Semaphore c_done(0);
Semaphore mtx (1); // will use as mutex
int ncdone = 0; // number of consumers done consuming

// each producer gets an id, which is pno
void a_function (int pno){
    while (true){
        
        a_done.P();
        
        mtx.P();
        buffer ++;
        cout << "I am A [" << pno << "] left buffer=" << buffer << endl;
        mtx.V();
        
        for (int i=0; i<2; i++)
            b_done.V();
    }
}
// each consumer gets an id cno
void b_function (int cno){
    while (true){
        b_done.P();
        
        mtx.P();
        cout << ">>>>>>>>>>>>>>>>>>>>I am B [" <<cno<<"] <<<<<<<<<<" << endl;
        mtx.V();
        usleep (500000);
        
        mtx.P();
        ncdone ++;
        if (ncdone == 2){ // it is the last one
            //a_done.V(); // so wake up the producer
            c_done.V();
            ncdone = 0; // reset the counter
        }
        mtx.V();
    }
}

void c_function (int cnum){
    while (true) {
        c_done.P();
        
        mtx.P();
        cout << "I am C [" << cnum << "] thread "<< endl << endl;
        a_done.V();
        mtx.V();
    }
}


int main (){
    vector<thread> a;
    vector<thread> b;
    vector<thread> c;
    
    for (int i=0; i< 100; i++)
        a.push_back(thread (a_function, i+1));
    
    for (int i=0; i< 100; i++)
        b.push_back(thread (b_function, i+1));
    
    for (int i=0; i< 100; i++)
        c.push_back(thread (c_function, i+1));
    
    for (int i=0; i<a.size (); i++)
        a[i].join();
    
    for (int i=0; i<b.size (); i++)
        b[i].join();
    
    for (int i=0; i<c.size (); i++)
        c[i].join();
}

