#include "DoublyLinkedList.h"
#include <iomanip>
#include <sstream>
using namespace std;

DoublyLinkedList::DoublyLinkedList()
{

}

DoublyLinkedList::DoublyLinkedList(int val)
{
	Node* next1 = new Node(val);
	head = next1;
	tail = next1;
}

DoublyLinkedList::~DoublyLinkedList()
{

}

void DoublyLinkedList::insert_back(int val)
{
	Node* next1 = new Node(val);
	if (head == nullptr || tail == nullptr) {
		tail = next1;
		head = next1;
	}
	else{
		
		tail->next = next1;
		next1->prev = tail;
		next1->next = nullptr;
		tail = next1;

	}
}

void DoublyLinkedList::insert_front(int val)
{
	Node* next1 = new Node(val);
	if (head == nullptr || tail == nullptr)
	{
		tail = next1;
		head = next1;
	}
	else {
		head->next = next1;
		next1->prev = head;
		next1->prev = nullptr;
		head = next1;
	}
}
void DoublyLinkedList::insert_at(int val, int idx)
{
	Node* next1 = new Node(val);
	Node* front = new Node();
	Node* curr = new Node();
	if (head == nullptr && tail == nullptr)
	{
		head = next1;
		tail = next1;
	}
	else {
		curr = head;
		int count = 0;
		if (idx < 0) {
			throw runtime_error("error");
		}
		else {
			if (head == NULL)
			{
				throw runtime_error("error");
			}
			else{
				if (idx == 0)
				{
					DoublyLinkedList::insert_front(val);
				}
				else {
					while (curr->next != NULL && count != idx) {
						front = curr;
						curr = curr->next;
						count = count + 1;
					}
					if (count == idx - 1) {
						DoublyLinkedList::insert_back(val);
					}
					else if (count != idx) {
						throw runtime_error("error");
					}
					else {
						front->next = next1;
						next1->next = curr;
						next1->prev = front;
						curr->prev = next1;
					}
				}
			}
		}
	}

}

Node& DoublyLinkedList::find(int val)
{
	Node* curr = new Node();
	curr = head;
	while (curr->next != nullptr) {
		if (curr->data == val) {
			return *curr;
		}
		curr = curr->next;
	}
	if (curr->data == val) {
		return *curr;
	}

	if(curr->next == nullptr){
		throw runtime_error("error");
	}
	
}

void DoublyLinkedList::delete_at(int idx)
{
	Node*  n= new Node();
	Node*  front= new Node();
	Node* curr = new Node();
	int count = 0;
	n = head;
	curr = head;
	int count2 = 0;
	while (n != nullptr) {
		count = count + 1;
		n = n->next;
	}
	if (count < idx) {
		throw runtime_error("error");
	}


	if (head != NULL)
	{
		if (idx == 0) {

			head = curr->next;
			curr->next = nullptr;
			curr->prev = nullptr;
		}
		else {
			while (curr->next != NULL && count2 != idx)
			{
				front = curr;
			  curr = curr->next;
				count2++;
			}
			if (curr == tail) {
				tail = curr->prev;
				curr->prev->next = nullptr;
			}
			else if (count2 != idx) {
				throw runtime_error("error");
			}
			else {
				front->next = curr->next;
				curr->next->prev = front;
			}
		}
	}
}

Node& DoublyLinkedList::get_head()
{
    return *head;
}

Node& DoublyLinkedList::get_tail()
{
    return *tail;
}

Node const& DoublyLinkedList::get_head() const
{
    return *head;
}

Node const& DoublyLinkedList::get_tail() const
{
    return *tail;
}

ostream& operator<<(ostream &os, DoublyLinkedList const& ll) {
    os << "Doubly Linked List" << endl;
    if (&(ll.get_head()) == nullptr)
        return (os << "Empty" << endl);
    os << "Head: " << &(ll.get_head()) << "\t Tail: " << &(ll.get_tail()) << endl;
    Node const* curr = &(ll.get_head());
    os << "Nodes (accessible from head to tail):" << endl << endl;
    os << setw(16) << setfill(' ') << ' ' << ' ' << center("prev", 15) << ' ' << center("data", 15) << ' ' << center("next", 15) << endl;
    while (curr != nullptr) {
        ostringstream oss; oss << (curr->prev); string prev = oss.str(); oss.str(""); oss << (curr->next); string next = oss.str(); oss.str(""); oss << (curr->data); string data = oss.str(); oss.str(""); oss << curr; string address = oss.str();
        os << setw(16) << setfill(' ') << ' ' << '.' << setw(16) << setfill('-') << '.' << setw(16) << '.' << setw(16) << '.' << endl;
        os << setw(16) << setfill(' ') << center(address,15) << '|' << setw(15) << setfill(' ') << center(prev, 15) << '|' << setw(15) << center(data, 15) << '|' << setw(15) << center(next, 15) << '|'<< endl;
        os << setw(16) << setfill(' ') << ' ' << '\'' << setw(16) << setfill('-') << '\'' << setw(16) << '\'' << setw(16) << '\'' << endl;
        os << endl;
        curr = curr->next;
    }
    return os;
}

string center (const string &str, const int col_width)
{
    // quick and easy (but error-prone) implementation
    int padl = (col_width - str.length()) / 2;
    int padr = (col_width - str.length()) - padl;
    string strf = string(padl, ' ') + str + string(padr, ' ');
    return strf;
}