//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <cmath>
#include <vector>

int maxm(vector<int>A, int size){
    int max = A.at(0);
    for (int i = 0; i < size; i++) {
        if (A.at(i) > max) {
            max = A.at(i);
        }
    }
    return max;
}

void countSort(vector<int>A, int n, int a)
{
   vector<int>output; // output array
    vector<int>count(10);
    for (int i = 0; i < n; i++)
        count[(A[i]/a)%10]++;
    
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[ (A[i]/a)%10 ] - 1] = A[i];
        count[ (A[i]/a)%10 ]--;
    }
    
    for (int i = 0; i < n; i++)
        A[i] = output[i];
}
void
RadixSort::sort(vector<int> A, int size)
{
    int max = maxm(A, size);
    for (int i = 1; max/i > 0; i *= 10){
        countSort(A, size, i);
    }
}
             
             
