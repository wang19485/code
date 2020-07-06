/* 
 *  main function
 */

#include "BTree.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

BTree read_file(string file_name)
{
  BTree tree;
    ifstream inf;
    inf.open(file_name);
    if (!inf.is_open()) {
        throw runtime_error("Error: can't open");
    }
    inf >> tree;
    inf.close();
    
    cout << "size: " << tree.get_size() << "\t";
    tree.update_search_cost();
    cout << endl;
    
    ofstream outf;
    string s = file_name + ".txt";
    outf.open(s);
    outf << tree;
    outf.close();
    return tree;
}


int main()
{
    try {
        // Because the process of finding average search or inorder processing for linear bst cost            spend too much time, the 12-times-loop is only work for perfect binary tree.
        for (int i = 1; i <= 12; i++){
            string s = to_string(i) + "p";
            read_file(s);
         }
        for (int i = 1; i <= 4; i++) {
            BTree tree1;
            BTree tree2;
            BTree tree3;
            string s = to_string(i) + "p";
            tree1 = read_file(s);
            tree1.print_level_by_level(cout);
            string sr = to_string(i) + "r";
            tree2 = read_file(sr);
            tree2.print_level_by_level(cout);
            string sl = to_string(i) + "l";
            tree3 = read_file(sl);
            tree3.print_level_by_level(cout);
        }
        
        //Test search, copy constructor, copy assignment operator using "4p" input file
        BTree tree;
        tree = read_file("4p");
        //Test case for search:
        cout << "address of node of search: " << tree.search(4) << endl << endl; // search 4 for example
        //Test case for copy constructor:
        BTree tree1(tree);
        cout << "Copy constructor: " << endl << tree1 << endl;
        //Test case for copy assignment operator
        BTree tree2;
        tree2 = tree;
        cout << "Copy assignment: " << endl << tree2 << endl;
        
    } catch (runtime_error& e) {
        cout << e.what();
    }
    
}

