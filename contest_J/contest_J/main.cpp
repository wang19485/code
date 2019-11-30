#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int num = 0;
    int key = 0;
    cin >> num >> key;
    vector<int>v1;
    vector<int>v2;
    for (int i = 0; i < num; i++) {
        int temp = 0;
        cin >> temp;
        v1.push_back(temp);
    }
    for (int i = 0; i < num; i++) {
        int temp = 0;
        cin >> temp;
        v2.push_back(temp);
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    //int max = v1.back();
    int count = 0;
    for (long int i = v1.size()-1; i >= 0; i--) {
        for (int j = 0; j < v2.size(); j++) {
            if (v1.at(i) * v2.at(j) >= key) {
                v1.at(i) = 0;
                v2.at(j) = 0;
                ++count;
            }
        }
    }
    cout << count << endl;
}
