#include <iostream>
using namespace std;

int maxArray(int array[], int size, int max){
    if (size==0) {
        return max;
    }
    if (array[size] > max) {
        max = array[size];
    }
    return maxArray(array, size-1,max);
}
int main() {
    int array1[] = {1,10,3,2,4};
    int array2[] = {2,6,4,7,9,20};
    int max1 = array1[0];
    int max2 = array2[0];
    cout << "Max for array1: " << maxArray(array1, 4, max1) << endl;
    cout << "Max for array2: " << maxArray(array2, 5, max2) << endl;
}
