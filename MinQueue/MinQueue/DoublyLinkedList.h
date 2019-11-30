#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;
class DoublyLinkedList; // class declaration

// list node
struct DListNode {
  int obj;
  DListNode *prev, *next;
  DListNode(int e=0, DListNode *p = NULL, DListNode *n = NULL)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list
class DoublyLinkedList {
private:
  DListNode header, trailer;
public:
  DoublyLinkedList() : header(0), trailer(0) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList(const DoublyLinkedList& dll); // copy constructor
  DoublyLinkedList(DoublyLinkedList&& dll); // move constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList& operator=(const DoublyLinkedList& dll); // assignment operator
  DoublyLinkedList& operator=(DoublyLinkedList&& dll); // move assignment operator
  // return the pointer to the first node
  DListNode *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  int first() const; // return the first object
  int last() const; // return the last object
  void insertFirst(int newobj); // insert to the first of the list
  int removeFirst(); // remove the first node
  void insertLast(int newobj); // insert to the last of the list
  int removeLast(); // remove the last node
  void insertAfter(DListNode &p, int newobj);
  void insertBefore(DListNode &p, int newobj);
  int removeAfter(DListNode &p);
  int removeBefore(DListNode &p);
};

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll);
// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll);

class DoublyLinkedQueue {
private:
    DoublyLinkedList ll; // internal LinkedList object
public:
    DoublyLinkedQueue() : ll() { } // constructor
    ~DoublyLinkedQueue() { ll.~DoublyLinkedList(); } // destructor
    bool isEmpty() const {  return ll.isEmpty();  }
    int size();
    int min();
    void enqueue(int elem) { ll.insertLast(elem); }
    int dequeue();
};

