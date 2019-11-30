//
//  main.cpp
//  reference
//
//  Created by 王英鉴 on 2018/10/11.
//  Copyright © 2018年 王英鉴. All rights reserved.
//

#include <iostream>
using namespace std;
int main() {
    int x = 27;
    int* y = &x;
    int** z = &y;
    cout << x << endl;
    cout << y << endl;
    cout << z << endl;
    cout << *y << endl;
    cout << *z << endl;
    cout << **z << endl;
}
