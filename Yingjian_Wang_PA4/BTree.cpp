/*
 * Binary Tree - source file (functions implementation)
 */

#include "BTree.h"
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

ostream& operator<<(ostream& out, BTree& tree)
{
  tree.print_level_by_level(out);
  tree.inorder(out,tree);
    out << endl << endl;
  return out;
}

ostream& operator<<(ostream& out, Node& node)
{
  out << "( "
      << node.value
      << ","
      << node.search_cost
      << " )";
  return out;
}

istream& operator>>(istream& in, BTree& tree)
{
    int ele;
    in >> ele;
    Node *newNode = new Node(ele);
    newNode->left = nullptr;
    newNode->right = nullptr;
    tree.set_root(newNode);
    int size = 0;
    while (!in.eof()) {
        in >> ele;
        ++size;
        Node *treeNode = tree.get_root();
        tree.insert(treeNode, ele);
    }
    tree.set_size(size+1);
  return in;
}

void BTree::copyTree(Node *&thisRoot, Node *&sourceRoot, int &i)
{
    
    if(sourceRoot == nullptr)
    {
        thisRoot = nullptr;
    }
    else
    {
        i++;
        thisRoot = new Node;
        thisRoot->value = sourceRoot->value;
        copyTree(thisRoot->left, sourceRoot->left,i);
        copyTree(thisRoot->right, sourceRoot->right,i);
    }
}

BTree::BTree(BTree& other)
{
    int i = 0;
    if(other.root == nullptr){
        root = nullptr;}
    else{
        this->size = other.get_size();
        copyTree(root, other.root,i);}
    size = i;
}

BTree::BTree(BTree&& other)
{
    this->set_root(other.get_root());
    other.set_root(nullptr);
}

BTree& BTree::operator=(BTree& other)
{
    int i = 0;
  if (this != &other) {
      if(other.root == nullptr){
          root = nullptr;}
      else{
          //size = 7;
          copyTree(root, other.root,i);}
  }
    size = i;
  return *this;
}

BTree& BTree::operator=(BTree&& other)
{
  if (this != &other) {
      this->set_root(other.get_root());
      other.set_root(nullptr);
  }
  return *this;
}

Node* BTree::insert(Node *treeNode, int obj)
{
    Node *node = new Node(obj);
    while (treeNode != node) {
        if (node->value < treeNode->value) {
            if (treeNode->left == nullptr) {
                treeNode->left = node;
                treeNode = node;
            }else{
                treeNode = treeNode->left;
            }
        }
        
        if (node->value > treeNode->value) {
            if (treeNode->right == nullptr) {
                treeNode->right = node;
                treeNode = node;
            }else{
                treeNode = treeNode->right;
            }
        }
    }
    return nullptr;
}

Node* BTree::search(int obj)
{
    if (obj == root->value) {
        return root;
    }
    Node *treeNode = root;
    while (!treeNode->is_leaf()) {
        if (obj < treeNode->value) {
            if (treeNode->left == nullptr) {
                return nullptr;
            }else{
                treeNode = treeNode->left;
                if (treeNode->value == obj) {
                    return treeNode;
                }
            }
        }
        
        if (obj > treeNode->value) {
            if (treeNode->right == nullptr) {
                return nullptr;
            }else{
                treeNode = treeNode->right;
                if (treeNode->value == obj) {
                    return treeNode;
                }
            }
        }
    }
  return nullptr;
}

void BTree::update_search_cost()
{
  /*
    do a BFS of your tree and update the search cost of all nodes
  */
    Node *treeNode = get_root();
    //out << treeNode->value <<"[1]"<< endl;
    vector<Node*>v(1);
    v[0] = treeNode;
    root->search_cost = 1;
    vector<Node*>v2(2);
    vector<int>table;
    //vector<int>num;
    //num.push_back(treeNode->value);
    table.push_back(1);
    int check = 0;
    int count = 0;
    double sum = 1;
    int cost = 0;
    while (check == 0) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == nullptr) {
                v2[(i+1)*2-2] = nullptr;
            }else{
                v2[(i+1)*2-2] = v[i]->left;
            }
            if (v[i] == nullptr) {
                v2[(i+1)*2-1] = nullptr;
            }else{
                v2[(i+1)*2-1] = v[i]->right;
            }
        }
        for (int i = 0; i < v2.size(); i++) {
            if (v2[i] == nullptr) {
                ++count;
            }
        }
        ++cost;
        if (count != v2.size()) {
            for (int i = 0; i < v2.size(); i++) {
                if (v2[i] == nullptr) {
                    //out << "X ";
                }else{
                    table.push_back(cost+1);
                    v2[i]->search_cost = cost+1;
                    //out << v2[i]->value <<"[" << v2[i]->search_cost << "]" << " ";
                    sum = sum + v2[i]->search_cost;
                    //num.push_back(v2[i]->value);
                }
            }
        }
        
        v = v2;
        if (count == v.size()) {
            check = 1;
        }
        vector<Node*>v3(2*v2.size());
        v2 = v3;
        count = 0;
    }
    
    cout << "Average search cost is: " << sum/table.size() << endl;
}

void BTree::inorder(ostream& out, BTree& tree)
{
    Node *curr = tree.get_root();
    stack<Node *>s;
    out << "In order: " << endl;
    while (curr != nullptr || s.empty() == false) {
        while (curr != nullptr)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        out << curr->value << "[" << curr->search_cost << "] ";
        curr = curr->right;
    }
  return;
}

void BTree::print_level_by_level(ostream& out)
{
    Node *treeNode = get_root();
    out << treeNode->value <<"[1]"<< endl;
    vector<Node*>v(1);
    v[0] = treeNode;
    root->search_cost = 1;
    vector<Node*>v2(2);
    vector<int>table;
    vector<int>num;
    num.push_back(treeNode->value);
    table.push_back(1);
    int check = 0;
    int count = 0;
    double sum = 1;
    int cost = 0;
    int size = 1;
    while (check == 0) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == nullptr) {
                v2[(i+1)*2-2] = nullptr;
            }else{
                v2[(i+1)*2-2] = v[i]->left;
            }
            if (v[i] == nullptr) {
                v2[(i+1)*2-1] = nullptr;
            }else{
                v2[(i+1)*2-1] = v[i]->right;
            }
        }
        for (int i = 0; i < v2.size(); i++) {
            if (v2[i] == nullptr) {
                ++count;
            }
        }
        ++cost;
        if (count != v2.size()) {
            for (int i = 0; i < v2.size(); i++) {
                if (v2[i] == nullptr) {
                    out << "X ";
                }else{
                    size++;
                    table.push_back(cost+1);
                    v2[i]->search_cost = cost+1;
                    out << v2[i]->value <<"[" << v2[i]->search_cost << "]" << " ";
                    sum = sum + v2[i]->search_cost;
                    num.push_back(v2[i]->value);
                }
            }
        }
        out << endl;
        v = v2;
        if (count == v.size()) {
            check = 1;
        }
        vector<Node*>v3(2*v2.size());
        v2 = v3;
        count = 0;
    }
    out << "Value\tSearch Cost" << endl;
    for (int i = 0; i < num.size(); i++) {
        out << num[i] << "\t\t" << table[i] << endl;
    }
    out << "The total number of node is " << size <<"."<< endl;
    out << "The search cost over all codes in the tree is ";
    for (long int i = 0; i < table.size(); i++) {
        if (i == table.size() - 1) {
            out << table[i];
        }else{
            out << table[i] << " + ";
        }
    }
    out << " = " << sum << endl;
    out << "Average search cost is: " << sum/table.size() << endl;
  return;
}


