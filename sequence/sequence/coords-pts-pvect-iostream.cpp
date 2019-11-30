#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

int main(int argv, char* argc[])
{
    if (argv != 2) {
        cerr << "Usage: ./a.out filename.dat" << endl;
        return 1;
    }
    string inputFile = argc[1];
    cout << "File with input data : " << inputFile << endl;
    
    ifstream inFs;
    inFs.open(inputFile); // open file
    
    string xt = ""; // variable x
    string yt = ""; // variable y
    vector<string>x; // vector x
    vector<string>y; // vector y
   
    while (!inFs.eof()) {
        getline(inFs,xt,','); // get value before ','
        getline(inFs,yt,'\n'); // get value before next line
        x.push_back(xt);
        y.push_back(yt);
    } // write the file into vector x and y
    
    inFs.close(); // close file
    
    double xd = 0; // temporary variable for x
    double yd = 0; // temporary variable for y
    vector<double>xv;
    vector<double>yv;
    
    for (int i = 0; i<x.size(); ++i) {
        xd = atof(x.at(i).c_str());
        yd = atof(y.at(i).c_str());
        xv.push_back(xd);
        yv.push_back(yd);
    } // convert string to double
    
    vector<double>sets; // a vector to store all distance for a point
    vector<double>sets2; // a vector to store index of points which have minimum distance
    double dis = 0; // declare distancfe
    double min = 0; // declare minimum
    
    for (int i = 0; i<xv.size(); ++i) {
        
        for (int j = 0; j < xv.size(); ++j) {
             dis = sqrt(pow(xv.at(i) - xv.at(j), 2) + pow(yv.at(i) - yv.at(j), 2)); // calculate distance
            //for debugging: cout << "(" << xv.at(i) << " - " << xv.at(j) << ")^2 + " << "(" << yv.at(i) << " - " << yv.at(j) << ")^2" << " = " << dis << endl;
                sets.push_back(dis);
        }
        min = 1000; // make sure the value is greater than every possible distance
        int po = 0; // declare the index of points
        for (int i = 0; i<sets.size(); ++i) {
            if (sets.at(i)!= 0 && min > sets.at(i)) {
                min = sets.at(i); // find minimum
                po = i;
            }
        }
        sets.clear(); // clear vector for next time
        sets2.push_back(po); // store minimums
    }
    
    //for debugging: for (int i = 0; i < sets2.size(); ++i) {
    //                   cout << sets2.at(i) << endl;
    //}
    
    
    ofstream outFi;
    outFi.open("output.txt"); // open a output file
    if (outFi.is_open()) {
       for (int k = 0; k<sets2.size(); ++k) {
          outFi << xv.at(k) << "," << yv.at(k) << "," << sets2.at(k) << endl; // write in
       }
    outFi.close();
    
    } else {
        cout << "Unable to open." << endl; // check output file is opened
    }
    return 0;
}
