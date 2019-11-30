//
//  main.cpp
//  insertion_sort
//
//  Created by 王英鉴 on 2019/2/11.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    int n = 0;
    cout << "Input: " << endl;
    cin >> n;
    int array[n];
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    clock_t t1, t2;
    t1 = clock();
    int gap,temp;
    
    for (gap = n/2; gap > 0; gap/=2) {
        for (int i = gap; i < n; i++) {
            temp = array[i];
            int a = i;
            while (a >=gap && array[a-gap] > temp) {
                array[a] = array[a-gap];
                a = a - gap;
            }
            array[a] = temp;
        }
    }
    t2 = clock();
    double diff = (double)(t2 - t1)*1000/CLOCKS_PER_SEC;
    
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << array[i] << endl;
    }
    cout << endl;
    cout << "The timing is " << diff << " ms" << endl;
    int t[2] = [11,12];
    int* p = &t;
    cout << *p++ << " " << (*p)++;
    return 0;
}
