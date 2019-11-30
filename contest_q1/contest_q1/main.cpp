#include <iostream>
#include <vector>
using namespace std;

int main() {
    int input = 0;
    cin >> input;
    vector<int>v;
    int sum = 0;
    //int planets = 0;
    for (int i = 0; i < input; i++) {
        int p = 0;
        cin >> p;
        v.push_back(p);
    }
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    cout << "Hello " << sum << " worlds" << endl;
}
