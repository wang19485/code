//
//  main.cpp
//  virtual
//
//  Created by 王英鉴 on 2019/2/6.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;

class Progression
{
public:
    virtual int getNext(int a, int dr, int n) = 0;
    virtual int sum(int a, int dr, int n) = 0;
};

class ArithmeticProgression:public Progression
{
public:
    int getNext(int a, int dr, int n){
        int next = 0;
        next = a + n * dr;
        return next;
        //return 1;
    }
    
    int sum(int a, int dr, int n){
        int sum1 = 0;
        for (int i = 0; i <= n; i++) {
            sum1 += getNext(a, dr, i);
            cout << getNext(a, dr, i) << endl;
        }
        cout << endl;
        return sum1;
    }
};

class GeometricProgression:public Progression
{
public:
    int getNext(int a, int dr, int n){
        int next = a * pow(dr, n);
        return next;
    }
    
    int sum(int a, int dr, int n){
        int sum2 = 0;
        for (int i = 0; i <= n; i++) {
            sum2 += getNext(a, dr, i);
            cout << getNext(a, dr, i) << endl;
        }
        cout << endl;
        return sum2;
    }
};

int main() {
    ArithmeticProgression x;
    GeometricProgression y;
    cout << x.sum(1, 2, 5) << endl;
    cout << endl;
    cout << y.sum(1, 2, 5) << endl;
    return 0;
}
