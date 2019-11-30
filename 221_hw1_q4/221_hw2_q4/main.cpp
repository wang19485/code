//
//  main.cpp
//  221_hw2_q4
//
//  Created by 王英鉴 on 2019/2/6.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

template<typename T>
int binarySearch(T x, T size, vector<T>v){
    int count = 0;
    int mid = 0;
    int low = 0;
    int high = size-1;
    while (low<=high) {
        ++count;
        mid = (low + high)/2;
        if (v[mid] < x) {
            low = mid + 1;
            if (low == high && x == v[low]) {
                return count;
            }
        }else if(v[mid] > x){
            high = mid - 1;
            if (low == high && x == v[low]) {
                return count;
            }
        }
        else{
            return count;
        }
    }
    return count;
}

int main() {
    int x = 3;
    int y = 7;
    int z = 8;
    int size = 8;
    vector<int>v;
    for (int i = 0; i < 8; i++) {
        v.push_back(i);
    }
    cout << "Best case: ";
    cout << binarySearch(x, size, v) << endl;
    cout << "Worst case: ";
    cout << binarySearch(y, size, v) << endl;
    cout << "Unsuccessful: ";
    cout << binarySearch(z, size, v) << endl;
    return 0;
}
