#include <iostream>
#include <math.h>
#include <vector>
#include <ctime>

using namespace std;

vector<long long> v;

int sqrt_func(long long input,long long mark){
    int size = 0;
    long long root = floor(sqrt(input)) - mark;
    v.push_back(root);
    if (pow(root, 2) == input) {
        return 1;
    }else{
        size = 1+sqrt_func(input - pow(root,2),0);
    }
    return size;
}

int main() {
    cout << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    cout << endl;
    while (true) {
        int mode = 0;
        cout << "Choose mode: (1 => default random, 2 => first 50000), (ctrl+c to exit): ";
        cin >> mode;
        if (mode != 1 && mode != 2) {
            mode = 1;
        }
        cout << endl;
        srand((int)time(0));
        for (int i = 5; i <= 50000; i+=5) {
            //cout << mode << endl;
            long long g = 1;
            if (mode == 1) {
                while (g%5 != 0 || g == 0) {
                    g = rand() % 1000000;
                    //g = 100000000;
                    //g = 15;
                }
            }else{
                g = i;
            }
            
            bool check = false;
            long long mark = 0;
            while (check == false) {
                sqrt_func(pow(g,2)+pow(g-1,2),mark);
                int sum = 0;
                for (int k = 0; k < v.size(); k++) {
                    sum += v[k];
                }
                if (sum != 2*g - 1 || v[0] == g || v[0] == g - 1) {
                    if (mark > pow(g,2)+pow(g-1,2)) {
                        cout << "Fail on " << g << endl;
                        exit(-1);
                    }
                    check = false;
                    ++mark;
                    v.clear();
                }else{
                    cout << "2*" << g << "-1 = " << sum << " = ";
                    sort(v.begin(), v.end(), greater<long long>());
                    for (int j = 0 ; j < v.size(); j++) {
                        if (j != v.size()-1) {
                            cout << v[j] << "+";
                        }else{
                            cout << v[j] << endl;
                        }
                        
                    }
                    break;
                }
            }
            v.clear();
            if (mode == 1 && i == 25) {
                break;
            }
        }
        cout << endl;
        cout << "---------------------------------------------------------------------------" << endl;
        cout << endl;
    }
    
}
