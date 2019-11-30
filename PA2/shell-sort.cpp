//============================================================================
// Name        : shell-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <vector>

void
ShellSort::sort(vector<int>&A, int size)
{
  /* Complete this function with the implementation of shell sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
    int gap,temp;
    int num_cmps = 0;
    for (gap = size/2; gap > 0; gap/=2) {
        for (int i = gap; i < size; i++) {
            temp = A[i];
            int a = i;
            while (a >=gap &&(++num_cmps, A[a-gap] > temp)) {
				
                A[a] = A[a-gap];
                a = a - gap;
            }
            A[a] = temp;
        }
    }
}
