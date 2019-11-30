
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int sum = 0;
    int num = 0;
    cin >> num;
    vector<string>v;
    for (int i = 0; i < num; i++) {
        string temp;
        cin >> temp;
        v.push_back(temp);
    }
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == "uranium") {
            sum += 19;
        }else if (v[i] == "plutonium"){
            sum += 20;
        }else if (v[i] == "thorium"){
            sum += 12;
        }
    }
    cout << sum << endl;
}
