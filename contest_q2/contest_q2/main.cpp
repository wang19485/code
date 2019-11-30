#include <iostream>
#include <vector>
using namespace std;

int main() {
    int total;
    int tele_total;
    cin >> total >> tele_total;
    vector<int>v1;
    vector<int>allplanets;
    vector<int>non;
    for (int i = 0; i < tele_total; i++) {
        int temp=0;
        cin >> temp;
        v1.push_back(temp);
    }
    vector<vector<int>>vd;
    for (int i = 0; i < total; i++) {
        vector<int>tempv;
        int temp1;
        int temp2;
        int temp3;
        cin >> temp1 >> temp2 >> temp3;
        tempv.push_back(temp1);
        tempv.push_back(temp2);
        tempv.push_back(temp3);
        vd.push_back(tempv);
    }
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    for (int i = 0; i < tele_total; i++) {
        sum1 += vd.at(v1.at(i)-1).at(0);
        sum2 += vd.at(v1.at(i)-1).at(1);
        sum3 += vd.at(v1.at(i)-1).at(2);
    }
    vector<int>compare;
    compare.push_back(sum1);
    compare.push_back(sum2);
    compare.push_back(sum3);
    int min = compare.at(0);
    for (int i = 0; i < 3; i++) {
        if (compare.at(i) < min) {
            min = compare.at(i);
        }
    }
    for (int i = 0; i < total; i++) {
        allplanets.push_back(i+1);
    }
    //cout << "size: " << allplanets.size() << endl;
    //vector<int>non;
    for (int i = 0; i < total; i++) {
        for (int j = 0; j < v1.size(); j++) {
            if (allplanets.at(i)==v1.at(j)) {
                //break;
                allplanets[i] = 0;
                break;
            }
            else if(allplanets.at(i) != v1.at(j)) {
                //non.push_back(allplanets[i]);
            }
        }
    }
    for (int i = 0; i < allplanets.size(); i++) {
        if (allplanets[i] != 0) {
            non.push_back(allplanets[i]);
        }
    }
    vector<int>minv;
    for (int i = 0; i < non.size(); i++) {
        vector<int>compare1;
        compare1 = vd.at(non.at(i)-1);
        
        int min1 = compare1.at(0);
        for (int i = 0; i < 3; i++) {
            if (compare1.at(i) < min1) {
                min1 = compare1.at(i);
            }
        }
        minv.push_back(min1);
    }
    int sum11 = 0;
    for (int i = 0; i < minv.size(); i++) {
        sum11 += minv.at(i);
    }
    cout << min + sum11 << endl;
}
