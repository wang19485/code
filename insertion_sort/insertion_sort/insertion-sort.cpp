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
    int temp,a;
    for (int i = 1; i < n; i++) {
        temp = array[i];
        a = i-1;
        while (array[a]>temp && a >=0) {
            array[a+1] = array[a];
            a = a-1;
        }
        array[a+1] = temp;
    }
    t2 = clock();
    double diff = (double)(t2 - t1)*1000/CLOCKS_PER_SEC;
    
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << array[i] << endl;
    }
    cout << endl;
    cout << "The timing is " << diff << " ms" << endl;
    int i=11;
    int *pi=&i;
    cout << *pi++ << endl;
    return 0;
}
