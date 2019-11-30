#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int num = 0;
    int max = 0;
    cin >> num >> max;
    vector<vector<int>>vd;
    int count = 0;
    for (int i = 0; i < num; i++) {
        vector<int>v;
        for (int j = 0; j < 3; j++) {
            int temp = 0;
            cin >> temp;
            v.push_back(temp);
        }
        vd.push_back(v);
    }
    for (int i = 0; i < num; i++) {
        <#statements#>
    }
    cout << count << endl;
}
