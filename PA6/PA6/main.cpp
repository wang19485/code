#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <stack>
using namespace std;

class Graph{
private:
    vector<vector<int>> arr;
    vector<vector<int>> visit;
    stack<int> s;
    int vertice;
    int edge;
public:
    void read_file(string file_name);
    void show_input();
    bool possible_one_stroke();
    void find_path(int u);
    void reset_arr();
    void show_path();
    void reset_s();
    int get_edge(){ return edge; }
    vector<vector<int>> get_arr(){ return arr; }
    long int get_s_size(){ return s.size(); }
    int get_vertice(){ return vertice; }
};

void Graph::read_file(string file_name){
    ifstream inf;
    inf.open(file_name);
    if (!inf.is_open()) {
        throw runtime_error("Error: no such file to open");
    }
    int vertices = 0;
    int edges = 0;
    inf >> vertices >> edges;
    edge = edges;
    vertice = vertices;
    vector<vector<int>>temp(vertices+1,vector<int>(vertices+1,0));
    this->arr = temp;
    this->visit = temp;
    for (int i = 0; i < edges; i++) {
        int a = 0;
        int b = 0;
        inf >> a >> b;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }
}

void Graph::show_input(){
    for (int i = 1; i < arr.size(); i++) {
        cout << i;
        for (int j = 1; j < arr[i].size(); j++) {
            if (arr[i][j] == 1) {
                cout <<  " -> " << j;
            }
        }
        cout << endl;
    }
}

bool Graph::possible_one_stroke(){
    int oddNum = 0;
    for (int i = 0; i < arr.size(); i++) {
        int count = 0;
        for (int j = 0; j < arr[i].size(); j++) {
            if (arr[i][j] == 1) {
                ++count;
            }
        }
        if (count % 2 == 1) {
            ++oddNum;
        }
    }
    //cout << "oddNum: " << oddNum << endl;
    if (oddNum > 2) {
        return false;
    }else{
        return true;
    }
}

void Graph::find_path(int u){
    for (int i = 1; i <= vertice; i++) {
        if (arr[u][i] == 1 && visit[u][i] == 0) {
            visit[u][i] = visit[i][u] = 1;
            find_path(i);
            if (s.empty()) {
                s.push(i);
                s.push(u);
            }else{
                if (i == s.top()) {
                    s.push(i);
                    s.push(u);
                }else{
                    break;
                }
            }
        }
    }
}

void Graph::reset_arr(){
    vector<vector<int>> vi(arr.size(),vector<int>(arr[0].size(),0));
    this->visit = vi;
}

void Graph::show_path(){
    while (!s.empty()) {
        cout << "(" << s.top() << ",";
        s.pop();
        cout << s.top() << ")";
        if (s.size() != 1) {
            cout << " -> ";
        }else{
            cout << endl;
        }
        s.pop();
    }
}

void Graph::reset_s(){
    while (!s.empty()) {
        s.pop();
    }
}

int main() {
    try {
        for (int k = 1; k <= 10; k++) {
            Graph G;
            string filename = "g" + to_string(k) + ".txt";
            G.read_file(filename);
            cout << filename << ":" << endl;
            G.show_input();
            if (G.possible_one_stroke()) {
                cout <<"The graph can be drawn by one stoke." << endl;
                for (int i = 1; i < G.get_vertice(); i++) {
                    G.find_path(i);
                    G.reset_arr();
                    if (G.get_s_size() == 2*G.get_edge()) {
                        G.show_path();
                        break;
                    }else{
                        G.reset_s();
                    }
                }
            }else{
                cout << "The graph cannot be drawn by one stoke." << endl;
            }
            cout << endl;
        }
    } catch (runtime_error &e) {
        cout << e.what() << endl;
    }
}
