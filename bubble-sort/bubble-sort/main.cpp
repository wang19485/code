//
//  main.cpp
//  bubble-sort
//
//  Created by 王英鉴 on 2019/2/11.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;
class bubble{
public:
    vector<int> randArray(int size){
        vector<int>v;
        for (int i = 0; i < size; i++) {
            v[i] = rand();
        }
        return v;
    }
    
    vector<int> increaseOrder(vector<int>v){
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size()-1-i; j++) {
                if (v[j+1] < v[j]) {
                    int temp = v[j+1];
                    v[j+1] = v[j];
                    v[j] = temp;
                }
            }
        }
        return v;
    }
    
    vector<int> decreaseOrder(vector<int>v){
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size()-1-i; j++) {
                if (v[j+1] < v[j]) {
                    int temp = v[j+1];
                    v[j+1] = v[j];
                    v[j] = temp;
                }
            }
        }
        return v;
    }
};


int main() {
    int n = 0;
    cout << "Input: " << endl;
    cin >> n;
    int array[n];
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }
    
    int size1 = pow(10, 2);
    bubble m1;
    m1.randArray(size1);
    
    
    clock_t t1, t2;
    t1 = clock();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (array[j+1] < array[j]) {
                int temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
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
