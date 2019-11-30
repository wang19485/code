#include "functions.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char * argv[]) {
    string name = argv[0]; // initial a new string to the name of the executable program
    if (argc == 1) {
        printUsageInfo(name); // usage
        exit(1);
    }
    
    int count = 0;
    string input;
    bool arg1 = false; // initial argument 1
    bool arg2 = true; // initial argument 2
    vector<string>v;
    
    for (int i = 1; i <argc; ++i) {
        string a = argv[i];
        if (a.substr(0,2) == "-c"||a.substr(0,2) == "-C") { // arg1 is true if c or C
            arg1 = true;
        }else if (a.substr(0,2) == "-s"|| a.substr(0,2) == "-S") { // arg1 is true if s or S
            arg2 = false;
        }
        if (a.substr(0,1) == "-") { // error if all argument contain dash
            ++count;
        }
        else {
            input = a;
            v.push_back(input); // put all string in a vector
        }
        if (a.substr(0,1) == "-") {
            if (a.substr(0,2) != "-c" && a.substr(0,2) != "-C" && a.substr(0,2) != "-s" && a.substr(0,2) != "-S") {
                printUsageInfo(name); // usage error
                exit(3);
            }
        }
    }
    
    if (count == argc - 1) {
        printUsageInfo(name); // usage error
        exit(2);
    }else{
        for (int i = 0; i < v.size(); ++i) { // call function in a loop
            string original = v.at(i);
            bool f = isPalindrome(v.at(i), arg1, arg2);
            
            if (f == true) {
                cout << "\"" << original << "\"" << " is a palindrome." << endl;
            }else {
                cout << "\"" << original << "\"" << " is not a palindrome." << endl;
            }
        }
    }
}
