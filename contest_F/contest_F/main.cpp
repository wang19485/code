

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int main() {
    unsigned int num = 0;
    cin >> num;
    //int s = 0;
    int check = 0;
    long int in = 3;
    while (check == 0) {
        if (2*pow(in, 2) + ((pow(in, 2) - pow(in-2, 2)) * (in-2)) <= num) {
            ++in;
        }else{
            check = 1;
        }
    }
        cout << in-1 << endl;
}
