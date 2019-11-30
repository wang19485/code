//============================================================================
// Name        : selection-sort.cpp
// Author      : Yingjian Wang
// Date        : 2/11/2019
// Copyright   : Yingjian Wang
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <vector>

void
SelectionSort::sort(vector<int>A, int size)				// main entry point
{
  /* Complete this function with the implementation of selection sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
    num_cmps = 0;
    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; j < size; j++) {
            ++num_cmps;
            if (A[j] < A[i]) {
                int temp = A[j];
                A[j] = A[i];
                A[i] = temp;
            }
        }
    }
}
