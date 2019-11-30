//============================================================================
// Name        : radix-sort.cpp
// Author      : Tianming Deng
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <cmath>
#include <vector>
bool hasNegative(vector<int>&A,int size){
	bool neg = false;
	for (int i = 0; i < size; i++) {
        if (A[i] < 0) {
            neg = true;
			return neg;
        }
    }
	
	return false;
	
}
int minValue(vector<int>&A, int size){
    int min = A[0];
    for (int i = 0; i < size; i++) {
        if (A[i] < min) {
            min = A[i];
        }
    }
    return min;
}

int maxValue(vector<int>&A, int size){
    int max = A[0];
    for (int i = 0; i < size; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    return max;
}

void countSort(vector<int>&A, int n, int a)
{
    vector<int>output(n); // output vector 
	int i=0;
	vector<int>count(10);
    for (i = 0; i < n; i++)
        count[(A[i]/a)%10]++;
    
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (A[i]/a)%10 ] - 1] = A[i];
        count[ (A[i]/a)%10 ]--;
    }
    
    for (i = 0; i < n; i++)
        A[i] = output[i];
}
void
RadixSort::sort(vector<int> &A, int size)
{   
    if (hasNegative(A,size)){ 
		// if it has negative number;
		int min = minValue(A,size);
	    for (int i = 0; i < size; i++) {
           A[i] = A[i] - min; 
        }
		int max = maxValue(A, size);
		for (int i = 1; max/i > 0; i *= 10){
			countSort(A, size, i);
		}
		for (int i = 0; i < size; i++) {
           A[i] = A[i] + min; 
        }
    
    }
	if(!hasNegative(A,size)){
    int max = maxValue(A, size);
    for (int i = 1; max/i > 0; i *= 10){
        countSort(A, size, i);
    }
	}
}
             
             
