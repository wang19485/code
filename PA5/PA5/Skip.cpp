#include "Skip.h"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <algorithm>
#include <string>
using namespace std;

vector<int> Skip::read_file(string file_name){
    ifstream inf;
    inf.open(file_name);
    vector<int>v;
    while (!inf.eof()) {
        int i = 0;
        inf >> i;
        v.push_back(i);
    }
    return v;
}

void Skip::show_Skip(vector<list<Node> >v){
    for (long int j = v.size()-1; j >= 0; j--) {
        for (list<Node>::iterator i = v[j].begin(); i != v[j].end(); i++) {
            if (i->value == numeric_limits<int>::min()) {
                cout << "-inf ";
            }else if(i->value == numeric_limits<int>::max()){
                cout << "inf ";
            }else{
                cout << i->value << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

vector<list<Node> > Skip::insert_Skip(vector<int>in){
    srand((unsigned)time(NULL));
    vector<list<Node> >v;
    for (int i = 0; i < in.size(); i++) {
        int tail = 0;
        int count = -1;
        while (tail == 0) {
            if (rand()%2 == 0) { // 0 for tail
                ++count;
                tail = 1;
            }else{
                ++count;
            }
        }
        int ninf = numeric_limits<int>::min();
        int pinf = numeric_limits<int>::max();
        if (count >= v.size()) {
            long int pre = v.size();
            for (int k = 0; k < count+1-pre; k++) {
                list<Node>temp;
                v.push_back(temp);
            }
            for (long int k = count; k >= pre; k--) {
                v[k].push_back(Node(ninf, v[k].begin()));
                v[k].push_back(Node(pinf,--v[k].end()));
            }
            for (int j = 0; j <= count-1; ++j) {
                list<Node>::iterator it = v[count-j].begin();
                list<Node>::iterator it1 = v[count-j-1].begin();
                it->down = it1;
                list<Node>::iterator it2 = --v[count-j].end();
                list<Node>::iterator it3 = --v[count-j-1].end();
                it2->down = it3;
            }
        }
        
        list<Node>::iterator it = v[count].begin();
        list<Node>::iterator temp = v[count].end();
        for (int j = count; j >= 0; j--) {
            while( in[i] > it->value){
                ++it;
            }
            if (in[i] < it->value) {
                v[j].insert(it, Node(in[i], it--));
                temp->down = ++it;
                temp = it;
                --it;
                it = it->down;
            }
        }
        cout << "Add " << in[i] << " to skip list at level " << count << " comparisons" <<endl;
    }
    return v;
}

void Skip::delete_Skip(vector<list<int> >v,vector<int>in){
    for (long int i = in.size()-1; i >= 0; i--) {
        int cpr = 0;
        for (long int j = v.size()-1; j >= 0; j--) {
            for (list<int>::iterator k = v[j].begin(); k != v[j].end(); k++) {
                ++cpr;
                if (*k == in[i]) {
                    v[j].erase(k);
                    break;
                }
            }
            if (v[j].empty()) {
                v.pop_back();
            }
        }
        cout << "Delete " << in[i] <<" from skip list, " << cpr << " comparisons" << endl;
    }
}
