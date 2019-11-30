#include <iostream>
#include <vector>
using namespace std;

int main() {
    int num = 0;
    cin >> num;
    vector<int>input;
    for (int i = 0; i < num; i++) {
        int temp = 0;
        cin >> temp;
        input.push_back(temp);
    }
    int max = input.at(0);
    for (int i =0; i < input.size(); i++) {
        if (input.at(i) > max) {
            max = input.at(i);
        }
    }
    int out = 0;
    int check = 0;
    while (check == 0) {
        int count = 0;
        for (int i = 0; i < input.size(); i++) {
            int mo = max % input.at(i);
            if (mo == 0) {
                ++count;
            }else{
                ++max;
                continue;
            }
            if (count == input.size()) {
                out = max;
                check = 1;
            }
        }
    }
    cout << out << endl;
}
