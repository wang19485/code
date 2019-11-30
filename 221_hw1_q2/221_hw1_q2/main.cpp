//
//  main.cpp
//  221_hw1_q2
//
//  Created by 王英鉴 on 2019/2/6.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<double>c;
    vector<double>a;
    vector<double>b;
    cout << "Input elements of vector a: ";
    for (int i = 0; i < 3; i++){
        double tem = 0;
        cin >> tem;
        a.push_back(tem);
    }
    cout << "Input elements of vector b: ";
    for (int i = 0; i < 3; i++){
        double tem = 0;
        cin >> tem;
        b.push_back(tem);
    }
    for (int i = 0; i < a.size(); i++) {
        double sum = a.at(i) * b.at(i);
        c.push_back(sum);
        cout << c.at(i) << " ";
    }
    cout << endl;
    return 0;
}
