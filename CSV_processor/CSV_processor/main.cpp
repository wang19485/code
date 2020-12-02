#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <algorithm>

using namespace std;

void readFile(string fileName, vector<vector<string>>& tableVector){
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cout << "Fail to open csv file" << endl;
        exit(1);
    }
    
    string lineStr;
    
    while (getline(inFile,lineStr)) {
        stringstream ss(lineStr);
        string str;
        vector<string> lineVector;
        while (getline(ss, str, ',')) {
            lineVector.push_back(str);
        }
        tableVector.push_back(lineVector);
    }
    inFile.close();
}

int main(int argc, char *argv[]) {
    vector<vector<string>> tableConstant;
    readFile(argv[1], tableConstant);
    vector<vector<string>> tableWeekly;
    readFile(argv[2], tableWeekly);
    
    vector<vector<string>> tableRegister;
    readFile(argv[3], tableRegister);
    
    /*int mode = 0;
    mode = stoi(argv[4]);*/
    
    int count = 0;
    int countBefore = 0;
    int countPart = 0;
    int countTimeNot = 0;
    int countMember = 0;
    int countNameNot = 0;

    string outStr;
    string outStr2;
    string personTimeNot;
    string personNameNot;
    
    ofstream outFile("output.txt");
    ofstream outFile2("output2.txt");
//    cout << tableWeekly[6][2] << endl;
//    cout << tableConstant[245][0] << endl;
//    cout << tableWeekly.size() << endl;
    int countEmail = 0;
    for (int i = 1; i < tableWeekly.size(); i++) {
        for (int j = 1; j < tableRegister.size(); j++) {
            transform(tableWeekly[i][1].begin(),tableWeekly[i][1].end(),tableWeekly[i][1].begin(),::tolower);
            transform(tableRegister[j][2].begin(),tableRegister[j][2].end(),tableRegister[j][2].begin(),::tolower);
            if (tableWeekly[i][1] == tableRegister[j][2]) {
                ++countEmail;
                tableWeekly[i][3] = tableRegister[j][6];
            }
        }
        cout << tableWeekly[i][3] << endl;
    }
    
    cout << countEmail << endl;
    
    for (int i = 1; i < tableWeekly.size(); i++) {
        ++countMember;
        if (stoi(tableWeekly[i][2]) >= 50) {
            countBefore = count;
            for (int j = 3; j < tableConstant.size(); j++) {
                string frontName = tableConstant[j][3];
                frontName.pop_back();
                string backName = tableConstant[j][2];
                backName.erase(backName.begin(),backName.begin()+1);
                string fullName = frontName + " " + backName;
                
                transform(fullName.begin(),fullName.end(),fullName.begin(),::tolower);
                transform(tableWeekly[i][0].begin(),tableWeekly[i][0].end(),tableWeekly[i][0].begin(),::tolower);
                //cout << tableConstant[j][1] << " " << tableWeekly[i][3] << endl;
                if (fullName == tableWeekly[i][0] || stol(tableConstant[j][1]) == stol(tableWeekly[i][3])) {
                    ++count;
                    ++countPart;
                    
                    outStr += "T" + to_string(j+1);
                    outStr2 += "D" + to_string(i+1);
                    outFile << fullName << " -- " << "T" << to_string(j+1) << endl;
                    if (outStr != "" && countPart < 31) {
                        outStr += ",";
                        outStr2 += ",";
                    }
                    
                    if (countPart == 31) {
                        outStr += '\n';
                        outStr += '\n';
                        outStr2 += '\n';
                        outStr2 += '\n';
                        countPart = 0;
                    }
                    
                    break;
                }
            }
            if (countBefore == count) {
                ++countNameNot;
                personNameNot += tableWeekly[i][0] + " -- " + "A" + to_string(i+1) + '\n';
            }
        }else{
            ++countTimeNot;
            personTimeNot += tableWeekly[i][0] + " -- " + "A" + to_string(i+1) + '\n';
        }
    }
    outStr.pop_back();
    cout << outStr << endl;
    
    outFile << endl << "Total match: " << count << endl << endl;
    outFile << "<<<<<<<<<<<<<<<<<<<< Copy the scripts below separately >>>>>>>>>>>>>>>>>>>>" << endl << endl;
    outFile << outStr << endl;
    outFile2 << outStr2 << endl;
    outFile << endl << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    
    outFile << "Total number: " << countMember << endl << endl;
    outFile << "Number of person whose time is not enough: " << countTimeNot << endl << endl;
    outFile << "Person whose time is not enough (cell numbers are based on weekly report): " << endl << endl;
    outFile << personTimeNot << endl;
    outFile << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    
    outFile << "Number whose information not matched: " << countNameNot << endl << endl;
    outFile << "Person whose Name, Email and ID are not matched (cell numbers are based on weekly report): " << endl << endl;
    outFile << personNameNot << endl;
    
    outFile.close();
    outFile2.close();
}
