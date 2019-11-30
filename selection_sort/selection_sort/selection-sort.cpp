//
//  main.cpp
//  selection_sort
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
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (array[j] < array[i]) {
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
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
    return 0;
}
