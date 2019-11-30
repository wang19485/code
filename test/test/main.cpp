//
//  main.cpp
//  test
//
//  Created by 王英鉴 on 2018/10/8.
//  Copyright © 2018年 王英鉴. All rights reserved.
//

#include <iostream>
#include "fun.h"
#include <vector>
using namespace std;

void search(vector<int>& v, int num) {
    for (int i =0; i < v.size(); ++i) {
        if (v.at(i) == num) {
            num = num;
        } else {
            v.push_back(num);
        }
    }
}

int main() {
    string g = "Michael Nowak";
    cout << reverseWords(g) << endl;

    char a;
    int count = 0;
    for (int i = 97; i < 97+26; ++i) {
        a = i;
        ++count;
        cout << a << "(" << i << ")\t";
        if (count>=3 && count%3==0) {
            cout << endl;
        }
    }
}
