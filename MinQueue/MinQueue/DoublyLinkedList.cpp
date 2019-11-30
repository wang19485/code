#include "DoublyLinkedList.h"
#include <stdexcept>
#include <iostream>

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  /* Complete this function */
    if (dll.getFirst() != nullptr) {
        DListNode *oldNode = dll.getFirst();
        DListNode *current = new DListNode;
        current->obj = oldNode->obj;
        header.next = current;
        oldNode = oldNode->next;
        current->prev = &header;
        while (oldNode != dll.getAfterLast()) {
            DListNode *newNode = new DListNode;
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
DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& dll)
{
  /* Complete this function */
    header.next = &trailer;
    trailer.prev = &header;

    if (dll.getFirst() != nullptr) {
        DListNode *oldNode = dll.getFirst();
        DListNode *current = new DListNode;
        current->obj = oldNode->obj;
        header.next = current;
        oldNode = oldNode->next;
        current->prev = &header;
        while (oldNode != dll.getAfterLast()) {
            DListNode *newNode = new DListNode;
            newNode->obj = oldNode->obj;
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
            oldNode = oldNode->next;
        }
        current->next = &trailer;
        trailer.prev = current;
        
        DListNode *nextNode = dll.getFirst();
        DListNode *prevNode;
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
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll)
{
  // use if (this != &dll)
  /* Complete this function */
    if (this != &dll) {
        header.next = &trailer;
        trailer.prev = &header;
        if (dll.getFirst() != nullptr) {
            DListNode *oldNode = dll.getFirst();
            DListNode *current = new DListNode;
            current->obj = oldNode->obj;
            header.next = current;
            oldNode = oldNode->next;
            current->prev = &header;
            while (oldNode != dll.getAfterLast()) {
                DListNode *newNode = new DListNode;
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
DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& dll)
{
  // use if (this != &dll)
  /* Complete this function */
    if (this != &dll) {
        header.next = &trailer;
        trailer.prev = &header;
        
        if (dll.getFirst() != nullptr) {
            DListNode *oldNode = dll.getFirst();
            DListNode *current = new DListNode;
            current->obj = oldNode->obj;
            header.next = current;
            oldNode = oldNode->next;
            current->prev = &header;
            while (oldNode != dll.getAfterLast()) {
                DListNode *newNode = new DListNode;
                newNode->obj = oldNode->obj;
                current->next = newNode;
                newNode->prev = current;
                current = newNode;
                oldNode = oldNode->next;
            }
            current->next = &trailer;
            trailer.prev = current;
            
            DListNode *nextNode = dll.getFirst();
            DListNode *prevNode;
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
void DoublyLinkedList::insertFirst(int newobj)
{ 
    /* Complete this function */
    DListNode *newNode = new DListNode(newobj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj)
{
    /* Complete this function */
    DListNode *newNode = new DListNode(newobj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

// remove the first object from the list
int DoublyLinkedList::removeFirst()
{ 
    /* Complete this function */
    DListNode *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    int obj = node->obj;
    delete node;
    return obj;
}

// remove the last object from the list
int DoublyLinkedList::removeLast()
{
    /* Complete this function */
    DListNode *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    int obj = node->obj;
    delete node;
    return obj;
}

// destructor
DoublyLinkedList::~DoublyLinkedList()
{
    /* Complete this function */
    DListNode *nextNode = header.next;
    DListNode *prevNode;
    while (nextNode != &trailer) {
        prevNode = nextNode;
        nextNode = nextNode->next;
        delete prevNode;
    }
    header.next = &trailer;
    trailer.prev = &header;
}

// return the first object
int DoublyLinkedList::first() const
{ 
    /* Complete this function */
    if (isEmpty()) {
        throw EmptyDLinkedListException("Empty list");
    }
    return header.next->obj;
}

// return the last object
int DoublyLinkedList::last() const
{
    /* Complete this function */
    if (isEmpty()) {
        throw EmptyDLinkedListException("Empty list");
    }
    return trailer.prev->obj;
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode &p, int newobj)
{
    /* Complete this function */
    DListNode *newNode = new DListNode;
    DListNode *current = getFirst();
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
void DoublyLinkedList::insertBefore(DListNode &p, int newobj)
{
    /* Complete this function */
    DListNode *newNode = new DListNode;
    DListNode *current = getFirst();
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
int DoublyLinkedList::removeAfter(DListNode &p)
{
    /* Complete this function */
    int obj = 0;
    DListNode *current = getFirst();
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
int DoublyLinkedList::removeBefore(DListNode &p)
{
    /* Complete this function */
    int obj = 0;
    DListNode *current = getFirst();
    while (&p != current && current != trailer.next) {
        current = current->next;
    }
    if (current == trailer.next) {
        return 0;
    }
    DListNode *newNode = current;
    newNode->prev->prev->next = current;
    newNode->prev = newNode->prev->prev;
    obj = newNode->obj;
    return obj;
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll)
{
    /* Complete this function */
    DListNode *current = dll.getFirst();
    int count = 0;
    while (current != dll.getAfterLast()) {
        count++;
        current = current->next;
    }
    return count;
}

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll)
{
  
  /* Complete this function */
    DListNode *current = dll.getFirst();
    while (current != dll.getAfterLast()) {
        out << current->obj << " ";
        current = current->next;
    }
  return out;
}

int DoublyLinkedQueue::size(){
    DListNode *current = ll.getFirst();
    int count = 0;
    while (current != ll.getAfterLast()) {
        count++;
        current = current->next;
    }
    return count;
}

int DoublyLinkedQueue::min(){
    int min = 0;
    DListNode *current = ll.getFirst();
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

int DoublyLinkedQueue::dequeue()
{
    if ( ll.isEmpty() )
        throw "Access to an empty queue";
    return ll.removeFirst();
}

