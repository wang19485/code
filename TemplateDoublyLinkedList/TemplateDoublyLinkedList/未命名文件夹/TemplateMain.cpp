#include "TemplateDoublyLinkedList.h"
#include <iostream>
using namespace std;
int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DoublyLinkedList<double> dll;
  cout << "list: " << dll << endl << endl;
  
  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertLast(i+0.1);
  }
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertFirst(i+0.2);
  }
  cout << "list: " << dll << endl << endl;
  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  DoublyLinkedList<double> dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  DoublyLinkedList<double> dll3;
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
    DListNode<double> *node1 = dll2.getFirst();
    dll2.insertAfter(*node1, 5.1);
    cout << "list: " << dll2 << endl << endl;
    
    cout << "Call insertBefore: " << endl;
    dll2.insertBefore(*node1, 5.1);
    cout << "list: " << dll2 << endl << endl;
    
    cout << "Call removeAfter: " << endl;
    dll2.removeAfter(*node1);
    cout << "list: " << dll2 << endl << endl;
    
    cout << "Call removeBefore: " << endl;
    dll2.removeBefore(*node1);
    cout << "list: " << dll2 << endl << endl;
    
  cout << "Call DoublyLinkedLostLength:: " << endl;
  cout << DoublyLinkedListLength(dll2) << endl << endl;
  return 0;
}
