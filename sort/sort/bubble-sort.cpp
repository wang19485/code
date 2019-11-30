//============================================================================
// Name        : bubble-sort.cpp
// Author      : Yingjian Wang
// Date        : 2/11/2019
// Copyright   : Yingjian Wang
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"
#include <vector>

void
BubbleSort::sort(vector<int>A, int size)			// main entry point
{
  /* Complete this function with the implementation of bubble sort algorithm 
     Record number of comparisons in variable num_cmps of class Sort
  */
    num_cmps = 0;
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-1-i; j++) {
            ++num_cmps;
            if (A[j+1] < A[j]) {
                int temp = A[j+1];
                A[j+1] = A[j];
                A[j] = temp;
            }
        }
    }
}
