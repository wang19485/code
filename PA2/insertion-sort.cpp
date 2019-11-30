//============================================================================
// Name        : insertion-sort.cpp
// Author      : Yingjian Wang
// Date        : 2/11/2019
// Copyright   : Yingjian Wang
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"
#include <vector>

void
InsertionSort::sort(vector<int>&A,int size)				// main entry point
{
  /* Complete this function with the implementation of insertion sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
    num_cmps = 0;
    int temp,a;
    for (int i = 1; i < size; i++) {
        temp = A[i];
        a = i-1;
        while (A[a]>temp &&(++num_cmps, a >=0)) {
            A[a+1] = A[a];
            a = a-1;
        }
        A[a+1] = temp;
    }
}
