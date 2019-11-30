#include "functions.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

int main() {
    int number1 = 0;
    int number2 = 0;
    cin >> number1;
    cin >> number2;
    string name;
    cin >> name; //input file name
    
    ifstream inf;
    inf.open(name); // open file
    
    if (number1 < 0) { // check negetive input for row
        cout << "Error: negetive number for row." << endl;
        exit(2);
    }else if (number2 == 0) { // check non-integer for row
        cout << "Error: non-integer." << endl;
        exit(5);
    }
    
    if (!inf.is_open()) { // check if open file
        cout << "Error: not open." << endl;
        exit(1);
    }
    
    int dta = 0;
    vector<vector<int>>data;
    
    
    while (!inf.eof()) {
        for (int i = 0; i < number1; ++i) {
            vector<int>row;
            for (int j = 0; j < number2; ++j) {
                inf >> dta;
                row.push_back(dta);
            }
            data.push_back(row);
        }
    } //read file
    
    inf.close(); // close input file
    
    double min = data[0][0]; // initialize min
    double max = data[0][0]; // initialize max
    
    for (int i = 0; i < number1; ++i) {
        for (int j = 0; j < number2; ++j) {
            if (data[i][j] < min) {
                min = data[i][j]; // find minimum
            }
            else if (data[i][j] > max) {
                max = data[i][j]; // find maximum
            }
        }
    }
    
    double shade = 0;
    vector<int>shadeVector;
    vector<vector<int>>r;
    vector<vector<int>>g;
    vector<vector<int>>b;
    double shadeRound = 0;
    
    for (int i = 0; i < number1; ++i) {
        vector<int>r_row;
        vector<int>g_row;
        vector<int>b_row;
        for (int j = 0; j < number2; ++j) {
            shade = ((data[i][j] - min) / (max - min)) * 255.0; // calculate shade
            shadeRound = round(shade); // round rgb value
            r_row.push_back(shadeRound);
            g_row.push_back(shadeRound);
            b_row.push_back(shadeRound);
        }
        r.push_back(r_row);
        g.push_back(g_row);
        b.push_back(b_row);
    }
    /*int color_r = 252;
    int color_g = 25;
    int color_b = 63;
    int start = 200;
    colorPath(data, r, g, b,color_r,color_g, color_b, start);*/
    
    ofstream outfi;
    string outputName = "";
    outputName = name + ".ppm";
    outfi.open(outputName); // open output file
    outfi << "P3" << endl;
    outfi << number2 << " " << number1 << endl;
    outfi << "255" << endl;
    for (int i = 0; i < number1; ++i) {
        for (int j = 0; j < number2; ++j) {
            outfi << r[i][j]<< " " << g[i][j] << " " << b[i][j]; // write into the file
        }
        cout << endl;
    }
    outfi.close(); // close output file
    return 0;
}

