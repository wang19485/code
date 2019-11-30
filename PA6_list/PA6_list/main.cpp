#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <list>
#include <stack>
using namespace std;

int main(){
    list<int>v;
    for (int i = 0; i < 5; i++) {
        v.push_back(i);
    }
    list<int>::iterator ptr = v.begin();
    list<int>::iterator ftr = v.end();
    cout << *ftr << endl;
    --ftr;
    //ftr;
    cout << *ftr << endl;
}
