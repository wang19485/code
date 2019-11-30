#include <cstdlib>
#include <iostream>
using namespace std;
//template <typename T>
//class DoublyLinkedList; // class declaration

// list node
template <typename T>
struct DListNode {
  T obj;
  DListNode *prev, *next;
  DListNode(T e= T(), DListNode *p = NULL, DListNode *n = NULL)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list
template <typename T>
class DoublyLinkedList {
private:
  DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList(const DoublyLinkedList& dll); // copy constructor
  DoublyLinkedList(DoublyLinkedList&& dll); // move constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList& operator=(const DoublyLinkedList& dll); // assignment operator
  DoublyLinkedList& operator=(DoublyLinkedList&& dll); // move assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; }
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void insertAfter(DListNode<T> &p, T newobj);
  void insertBefore(DListNode<T> &p, T newobj);
  T removeAfter(DListNode<T> &p);
  T removeBefore(DListNode<T> &p);
};

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);
// return the list length
template <typename T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll);

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
    explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& dll)
{
    // Initialize the list
    header.next = &trailer;
    trailer.prev = &header;
    /* Complete this function */
    if (dll.getFirst() != nullptr) {
        DListNode<T> *oldNode = dll.getFirst();
        DListNode<T> *current = new DListNode<T>;
        current->obj = oldNode->obj;
        header.next = current;
        oldNode = oldNode->next;
        current->prev = &header;
        while (oldNode != dll.getAfterLast()) {
            DListNode<T> *newNode = new DListNode<T>;
            newNode->obj = oldNode->obj;
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
            oldNode = oldNode->next;
        }
        current->next = &trailer;
        trailer.prev = current;
    }
}
// move constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& dll)
{
    /* Complete this function */
    header.next = &trailer;
    trailer.prev = &header;
    
    if (dll.getFirst() != nullptr) {
        DListNode<T> *oldNode = dll.getFirst();
        DListNode<T> *current = new DListNode<T>;
        current->obj = oldNode->obj;
        header.next = current;
        oldNode = oldNode->next;
        current->prev = &header;
        while (oldNode != dll.getAfterLast()) {
            DListNode<T> *newNode = new DListNode<T>;
            newNode->obj = oldNode->obj;
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
            oldNode = oldNode->next;
        }
        current->next = &trailer;
        trailer.prev = current;
        
        DListNode<T> *nextNode = dll.getFirst();
        DListNode<T> *prevNode;
        while (nextNode != &trailer) {
            prevNode = nextNode;
            nextNode = nextNode->next;
            delete prevNode;
        }
        header.next = &trailer;
        trailer.prev = &header;
    }
}

// assignment operator
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& dll)
{
    // use if (this != &dll)
    /* Complete this function */
    if (this != &dll) {
        header.next = &trailer;
        trailer.prev = &header;
        if (dll.getFirst() != nullptr) {
            DListNode<T> *oldNode = dll.getFirst();
            DListNode<T> *current = new DListNode<T>;
            current->obj = oldNode->obj;
            header.next = current;
            oldNode = oldNode->next;
            current->prev = &header;
            while (oldNode != dll.getAfterLast()) {
                DListNode<T> *newNode = new DListNode<T>;
                newNode->obj = oldNode->obj;
                current->next = newNode;
                newNode->prev = current;
                current = newNode;
                oldNode = oldNode->next;
            }
            current->next = &trailer;
            trailer.prev = current;
        }
    }
    return *this;
}
// move assignment operator
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& dll)
{
    // use if (this != &dll)
    /* Complete this function */
    if (this != &dll) {
        header.next = &trailer;
        trailer.prev = &header;
        
        if (dll.getFirst() != nullptr) {
            DListNode<T> *oldNode = dll.getFirst();
            DListNode<T> *current = new DListNode<T>;
            current->obj = oldNode->obj;
            header.next = current;
            oldNode = oldNode->next;
            current->prev = &header;
            while (oldNode != dll.getAfterLast()) {
                DListNode<T> *newNode = new DListNode<T>;
                newNode->obj = oldNode->obj;
                current->next = newNode;
                newNode->prev = current;
                current = newNode;
                oldNode = oldNode->next;
            }
            current->next = &trailer;
            trailer.prev = current;
            
            DListNode<T> *nextNode = dll.getFirst();
            DListNode<T> *prevNode;
            while (nextNode != &trailer) {
                prevNode = nextNode;
                nextNode = nextNode->next;
                delete prevNode;
            }
            header.next = &trailer;
            trailer.prev = &header;
        }
    }
    return *this;
}

// insert the new object as the first one
template <typename T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{
    /* Complete this function */
    DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

// insert the new object as the last one
template <typename T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
    /* Complete this function */
    DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

// remove the first object from the list
template <typename T>
T DoublyLinkedList<T>::removeFirst()
{
    /* Complete this function */
    DListNode<T> *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    T obj = node->obj;
    delete node;
    return obj;
}

// remove the last object from the list
template <typename T>
T DoublyLinkedList<T>::removeLast()
{
    /* Complete this function */
    DListNode<T> *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    T obj = node->obj;
    delete node;
    return obj;
}

// destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    /* Complete this function */
    DListNode<T> *nextNode = header.next;
    DListNode<T> *prevNode;
    while (nextNode != &trailer) {
        prevNode = nextNode;
        nextNode = nextNode->next;
        delete prevNode;
    }
    header.next = &trailer;
    trailer.prev = &header;
}

// return the first object
template <typename T>
T DoublyLinkedList<T>::first() const
{
    /* Complete this function */
    if (isEmpty()) {
        throw EmptyDLinkedListException("Empty list");
    }
    return header.next->obj;
}

// return the last object
template <typename T>
T DoublyLinkedList<T>::last() const
{
    /* Complete this function */
    if (isEmpty()) {
        throw EmptyDLinkedListException("Empty list");
    }
    return trailer.prev->obj;
}

// insert the new object after the node p
template <typename T>
void DoublyLinkedList<T>::insertAfter(DListNode<T> &p, T newobj)
{
    /* Complete this function */
    DListNode<T> *newNode = new DListNode<T>;
    DListNode<T> *current = getFirst();
    while (&p != current && current != trailer.prev) {
        current = current->next;
    }
    if (current == trailer.prev) {
        return;
    }
    newNode->obj = newobj;
    current->next->prev = newNode;
    newNode->next = current->next;
    current->next = newNode;
    newNode->prev = current;
}

// insert the new object before the node p
template <typename T>
void DoublyLinkedList<T>::insertBefore(DListNode<T> &p, T newobj)
{
    /* Complete this function */
    DListNode<T> *newNode = new DListNode<T>;
    DListNode<T> *current = getFirst();
    while (&p != current && current != nullptr) {
        current = current->next;
    }
    if (current == nullptr) {
        return;
    }
    newNode->obj = newobj;
    current->prev->next = newNode;
    newNode->prev = current->prev;
    current->prev = newNode;
    newNode->next = current;
}

// remove the node after the node p
template <typename T>
T DoublyLinkedList<T>::removeAfter(DListNode<T> &p)
{
    /* Complete this function */
    T obj = T();
    DListNode<T> *current = getFirst();
    while (&p != current && current != trailer.prev) {
        current = current->next;
    }
    if (current == trailer.prev) {
        return 0;
    }
    
    current->next->next->prev = current;
    current->next = current->next->next;
    obj = current->obj;
    return obj;
}

// remove the node before the node p
template <typename T>
T DoublyLinkedList<T>::removeBefore(DListNode<T> &p)
{
    /* Complete this function */
    T obj = T();
    DListNode<T> *current = getFirst();
    while (&p != current && current != trailer.next) {
        current = current->next;
    }
    if (current == trailer.next) {
        return 0;
    }
    DListNode<T> *newNode = current;
    newNode->prev->prev->next = current;
    newNode->prev = newNode->prev->prev;
    obj = newNode->obj;
    return obj;
}

// return the list length
template <typename T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll)
{
    /* Complete this function */
    DListNode<T> *current = dll.getFirst();
    int count = 0;
    while (current != dll.getAfterLast()) {
        count++;
        current = current->next;
    }
    return count;
}

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
    
    /* Complete this function */
    DListNode<T> *current = dll.getFirst();
    while (current != dll.getAfterLast()) {
        out << current->obj << " ";
        current = current->next;
    }
    return out;
}

template <typename T>
class DoublyLinkedQueue {
private:
    DoublyLinkedList<T> ll; // internal LinkedList object
public:
    DoublyLinkedQueue() : ll() { } // constructor
    ~DoublyLinkedQueue() { ll.~DoublyLinkedList(); } // destructor
    bool isEmpty() const {  return ll.isEmpty();  }
    int size();
    T min();
    void enqueue(T elem) { ll.insertLast(elem); }
    T dequeue();
};

template <typename T>
int DoublyLinkedQueue<T>::size(){
    return DoublyLinkedListLength(ll);
}

template <typename T>
T DoublyLinkedQueue<T>::min(){
    T min = T();
    DListNode<T> *current = ll.getFirst();
    min = current->obj;
    current = current->next;
    while (current != ll.getAfterLast()) {
        if (current->obj < min) {
            min = current->obj;
        }
        current = current->next;
    }
    return min;
}

template <typename T>
T DoublyLinkedQueue<T>::dequeue()
{
    if ( ll.isEmpty() )
        throw "Access to an empty queue";
    return ll.removeFirst();
}



