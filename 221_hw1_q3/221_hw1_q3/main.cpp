//
//  main.cpp
//  221_hw1_q3
//
//  Created by 王英鉴 on 2019/2/6.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class tf
{
public:
    bool function(vector<int>v){
        int count = 0;
        for (int i = 0; i < v.size(); i++) {
            for (int j = i+1; j < v.size(); j++) {
                ++count;
                if ((v.at(i) * v.at(j)) % 2 != 0) {
                    cout << "Operation times: " << count << endl << "Result: ";
                    return true;
                }
            }
        }
        cout << "Operation times: " << count << endl << "Result: ";
        return false;
    }
};

int main() {
    vector<int>v1; // 3 elements
    vector<int>v2; // 3 elements too
    for (int i = 1; i <= 5; i+=2) {
        v1.push_back(i);
    }
    //v1.push_back(1);
    //v1.push_back(2);
    //v1.push_back(3);
    for (int i = 0; i <= 4; i+=2) {
        v2.push_back(i);
    }
    tf a;
    tf b;
    cout << "Best case: " << endl;
    cout << a.function(v1) << endl;
    cout << endl;
    cout << "Worst case: " << endl;
    cout << b.function(v2) << endl;
    return 0;
}
