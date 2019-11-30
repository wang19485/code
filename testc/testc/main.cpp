//
//  main.cpp
//  testc
//
//  Created by 王英鉴 on 2019/10/16.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class test{
public:
    int a;
    int b;
    test(){};
};

int main() {
    //int g = 99;
    test *hh = new test();
    hh->a = 1;
    hh->b = 2;
    char *gg = (char*)hh;
    vector<char> v;
    v.push_back(*gg);
    test *gg1 = (test*)v[0];
    cout << v[0] << endl;
}
