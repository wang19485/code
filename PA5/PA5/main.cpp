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
#include <stdexcept>
using namespace std;

struct Node{
    int value;
    list<Node>::iterator down;
    Node(int val, list<Node>::iterator d):value(val),down(d){};
};

vector<int> read_file(string file_name){
    ifstream inf;
    inf.open(file_name);
    if (!inf.is_open()) {
        throw runtime_error("Error: no such file to open");
    }
    vector<int>v;
    while (!inf.eof()) {
        int i = 0;
        inf >> i;
        v.push_back(i);
    }
    return v;
}

void show_Skip(vector<list<Node> >v){
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
}

bool search(vector<list<Node> >v, int obj){
    if (v[v.size()-1].begin()->value == obj) {
        return true;
    }else{
        int cpr = 0;
        list<Node>::iterator it = v[v.size()-1].begin();
        for (long int j = v.size()-1; j >= 0; j--) {
            while( obj > it->value){
                ++it;
                ++cpr;
            }
            if (obj < it->value) {
                --it;
                it = it->down;
            }else if(obj == it->value){
                return true;
            }
        }
    }
    return false;
}

vector<list<Node> > insert_Skip(vector<int>in, int& total_of_insert){
    srand((unsigned)time(NULL));
    vector<list<Node> >v(0);
    int ninf = numeric_limits<int>::min();
    int pinf = numeric_limits<int>::max();
    for (int i = 0; i < in.size(); i++) {
        int cpr = 0;
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
        if (count >= v.size()) {
            long int pre = v.size();
            for (int k = 0; k < count+1-pre; k++) {
                list<Node>temp;
                v.push_back(temp);
            }
            for (long int k = count; k >= pre; k--) {
                v[k].push_back(Node(ninf, v[k].begin()));
                v[k].push_back(Node(pinf, --v[k].end()));
            }
            if (count > 0) {
                for (int j = 0; j <= count-1; j++) {
                    list<Node>::iterator it1 = v[count-j].begin();
                    list<Node>::iterator it2 = v[count-j-1].begin();
                    it1->down = it2;
                    list<Node>::iterator it3 = --v[count-j].end();
                    list<Node>::iterator it4 = --v[count-j-1].end();
                    it3->down = it4;
                }
            }
        }
        
        list<Node>::iterator it = v[v.size()-1].begin();
        list<Node>::iterator temp = --v[v.size()-1].end();
        for (long int j = v.size()-1; j >= 0; j--) {
            while( in[i] > it->value){
                ++it;
                ++cpr;
            }
            if (in[i] < it->value) {
                ++cpr;
                if (j <= count) {
                    Node node = Node(in[i],it);
                    v[j].insert(it, node);
                    --it;
                    temp->down = it;
                    temp = it;
                    --it;
                    it = it->down;
                }else{
                    --it;
                    it = it->down;
                }
            }
        }
        if (in.size() < 2*2*2*2) {
            cout << "Add " << in[i] << " to skip list at level " << count << ", "<< cpr <<" comparisons" <<endl;
        }
        total_of_insert += cpr;
    }
    return v;
}

void delete_Skip(vector<list<Node> >& v, vector<int> in, int& total_of_delete){
    
    for (long int i = in.size()-1; i >= 0; i--) {
        int cpr = 0;
        list<Node>::iterator it = v[v.size()-1].begin();
        for (long int j = v.size()-1; j >= 0; j--) {
            while( in[i] > it->value){
                ++it;
                ++cpr;
            }
            if (in[i] < it->value) {
                ++cpr;
                --it;
                it = it->down;
            }else if(in[i] == it->value){
                ++cpr;
                v[j].erase(it);
                it = it->down;
            }
            if (v[j].size() == 2) {
                v.erase(v.begin()+j);
            }
        }
        if (in.size() < 2*2*2*2) {
            cout << "Delete " << in[i] <<" from skip list, " << cpr << " comparisons" << endl;
        }
        total_of_delete += cpr;
    }
}


int main() {
    try {
        cout << "Perfect data: " << endl;
        for (int a = 1; a <= 12; a++) {
            string sp = to_string(a) + "p";
            vector<int>in;
            int total_of_insert = 0;
            int total_of_delete = 0;
            in = read_file(sp);
            cout << "Input size: " << in.size() << endl;
            vector<list<Node> >v;
            if (a < 5) {
                cout << "input: " << endl;
                for (int i = 0; i < in.size(); i++) {
                    cout << in[i] << endl;
                }
                cout << "Create a skip list:" << endl;
            }
            v = insert_Skip(in, total_of_insert);
            if (a < 5) {
                show_Skip(v);
            }
            cout << "Ex. Search 8 in the list (1 for found, 0 for not): " << search(v,8) << endl;
            if (a < 5) {
                cout << "Delete skip list: " << endl;
            }
            delete_Skip(v, in,total_of_delete);
            show_Skip(v); // Check if the vector v is empty. If it ouputs nothing, the vector is empty.
            double b = in.size();
            cout << "Average insert cost: " << total_of_insert/b << endl;
            cout << "Average delete cost: " << total_of_delete/b << endl << endl;
        }
        cout << "Linear data: " << endl;
        for (int a = 1; a <= 12; a++) {
            string sp = to_string(a) + "l";
            vector<int>in;
            int total_of_insert = 0;
            int total_of_delete = 0;
            in = read_file(sp);
            cout << "Input size: " << in.size() << endl;
            vector<list<Node> >v;
            if (a < 5) {
                cout << "input: " << endl;
                for (int i = 0; i < in.size(); i++) {
                    cout << in[i] << endl;
                }
                cout << "Create a skip list:" << endl;
            }
            v = insert_Skip(in, total_of_insert);
            if (a < 5) {
                show_Skip(v);
            }
            cout << "Ex. Search 8 in the list (1 for found, 0 for not): " << search(v,8) << endl;
            if (a < 5) {
                cout << "Delete skip list: " << endl;
            }
            delete_Skip(v, in,total_of_delete);
            show_Skip(v); // Check if the vector v is empty. If it ouputs nothing, the vector is empty.
            double b = in.size();
            cout << "Average insert cost: " << total_of_insert/b << endl;
            cout << "Average delete cost: " << total_of_delete/b << endl << endl;
        }
        cout << "Random data: " << endl;
        for (int a = 1; a <= 12; a++) {
            string sp = to_string(a) + "r";
            vector<int>in;
            int total_of_insert = 0;
            int total_of_delete = 0;
            in = read_file(sp);
            cout << "Input size: " << in.size() << endl;
            vector<list<Node> >v;
            if (a < 5) {
                cout << "input: " << endl;
                for (int i = 0; i < in.size(); i++) {
                    cout << in[i] << endl;
                }
                cout << "Create a skip list:" << endl;
            }
            v = insert_Skip(in, total_of_insert);
            if (a < 5) {
                show_Skip(v);
            }
            cout << "Ex. Search 8 in the list (1 for found, 0 for not): " << search(v,8) << endl;
            if (a < 5) {
                cout << "Delete skip list: " << endl;
            }
            delete_Skip(v, in,total_of_delete);
            show_Skip(v); // Check if the vector v is empty. If it ouputs nothing, the vector is empty.
            double b = in.size();
            cout << "Average insert cost: " << total_of_insert/b << endl;
            cout << "Average delete cost: " << total_of_delete/b << endl << endl;
        }
    } catch (runtime_error &e) {
        cout << e.what() << endl;
    }
    
    return 0;
}
