#include "TemplateDoublyLinkedList.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DoublyLinkedList<string> dll;
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    stringstream ss;
    ss << i;
    dll.insertLast(ss.str());
  }
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    stringstream ss;
    ss << i;
    dll.insertFirst(ss.str());
  }
  cout << "list: " << dll << endl << endl;
  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  DoublyLinkedList<string> dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  DoublyLinkedList<string> dll3;
  dll3=dll;
  cout << "list3: " << dll3 << endl << endl;
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeLast();
  }
  cout << "list: " << dll << endl << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeFirst();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl << endl;

  // more testing...
  // add tests for insertAfter, insertBefore
  // add tests for removeAfter, removeBefore
  // add tests for DoublyLinkedListLength
    cout << "Call insertAfter: " << endl;
    DListNode<string> *node1 = dll2.getFirst();
    stringstream ss1;
    ss1 << 5;
    dll2.insertAfter(*node1, ss1.str());
    cout << "list: " << dll2 << endl << endl;
    
    cout << "Call insertBefore: " << endl;
    dll2.insertBefore(*node1, ss1.str());
    cout << "list: " << dll2 << endl << endl;
    
    cout << "Call removeAfter: " << endl;
    dll2.removeAfter(*node1);
    cout << "list: " << dll2 << endl << endl;
    
    cout << "Call removeBefore: " << endl;
    dll2.removeBefore(*node1);
    cout << "list: " << dll2 << endl << endl;
    
    cout << "Call DoublyLinkedListLength:: " << endl;
    cout << DoublyLinkedListLength(dll2) << endl << endl;
    
    cout << "Create new list to test MinQueue and check isEmpty() (1 for true): ";
    DoublyLinkedQueue<string> ll;
    cout << ll.isEmpty() << endl << endl;
    
    cout << "Using enqueue to insert 20 nodes at back with value 10,20,30,..,100 twice." << endl;
    for (int j = 0; j < 2; j++) {
        for (int i=10;i<=100;i+=10) {
            stringstream ss2;
            ss2 << i;
            ll.enqueue(ss2.str());
        }
    }

    cout << "Call size(): " << ll.size() << endl << endl;
    cout << "Call min() to get the minimum of the list: " << ll.min() << endl << endl;
    
    cout << "Show the deleted 10 elements: ";
    for (int i = 0; i < 10; i++) {
        cout << ll.dequeue() << " ";
    }
    cout << endl;
    cout << "Call size(): " << ll.size() << endl << endl;
    
  return 0;
}
