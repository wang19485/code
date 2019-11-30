#include "functions.h"
#include <iostream>
using namespace std;

void printUsageInfo(string name){ // print out usage
    cout << "Usage: " << name <<" [-c] [-s] string ..." << endl;
    cout << "-c: turn on case sensitivity" << endl << "-s: turn off ignoring spaces" << endl;
}

void eraseSpace(string& name) { // erase space
    for (int i = 0; i < name.length(); ++i) {
        if ( isspace(name.at(i)) != 0) {
            name.erase(name.begin()+i);
        }
    }
}

void letter(string& name) { // convert to lowcase
    for (int i = 0; i < name.length(); ++i) {
        if (isupper(name.at(i)) != 0) {
            name.at(i) = tolower(name.at(i));
        }
    }
}

bool isPalindromeR(string inputString) {
    int count = 0;
    for (int i =0; i < inputString.length()/2; ++i) { // compare each letter in string
        if (inputString.at(i) != inputString.at(inputString.length()-1-i)) {
            ++count;
        }
    }
    if (count != 0) {
        return false;
    }
    return true;
}

bool isPalindrome(string inputString, bool arg1, bool arg2) {
    for (int i = 0; i < inputString.length(); ++i) { // find punctuation and remove it
        if (ispunct(inputString.at(i)) !=0) {
            inputString.erase(inputString.begin()+i);
        }
    }
    
    if (arg2 == true) {
        eraseSpace(inputString); // call eraseSpace function
    }
    
    if (arg1 == false) { // call 
        letter(inputString);
    }
    
    bool b = isPalindromeR(inputString);
    if (b == false) {
        return false;
    }
    return true;
}


