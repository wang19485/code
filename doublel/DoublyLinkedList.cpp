#include "DoublyLinkedList.h"
#include <iomanip>
#include <sstream>
using namespace std;

DoublyLinkedList::DoublyLinkedList()
{

}

DoublyLinkedList::DoublyLinkedList(int val)
{
    Node* n = new Node(val);
    head = n;
    tail = n;
}

DoublyLinkedList::~DoublyLinkedList()
{

}
void DoublyLinkedList::insert_back(){
}
void DoublyLinkedList::insert_back(int val)
{
	Node* n = new Node(val);
	if(head == nullptr || tail == nullptr)
	{
		head = n;
		tail = n;
	}
	else{
    
		tail->next = n;
		n->prev = tail;
		n->next = nullptr; 
		tail = n;
	}
}


void DoublyLinkedList::insert_front(int val)
{
    Node* n = new Node(val);
    if (head == nullptr)
        tail = n;
    n->next = head; head = n;
    if (n->next != nullptr)
        n->next->prev = head;
}

void DoublyLinkedList::insert_at(int val, int idx)
{
    Node* front = new Node();
    Node* curr = new Node();
    Node* n = new Node(val);
	
	if(head == nullptr && tail == nullptr)
	{
		head = n;
		tail = n;
	}
	else{
		
    curr = head;
	int i = 0;
	
	
	if(idx<0){
		throw runtime_error("error");
	}
	else{
		

    if(head != NULL)
    {
        if(idx==0)
        {
            DoublyLinkedList::insert_front(val);
        }
        
        else
        {
            while(curr->next != NULL && i != idx)
            {
            //loop to the position
            front = curr;
            curr = curr->next;
			++i;
            }
            if(i+1 ==idx){
				DoublyLinkedList::insert_back(val);
			}
			else if(i !=idx){
			
				throw runtime_error("error");
			}
			
			else{
				
				front->next = n;
				n->next = curr;
				n->prev = front;
				curr->prev = n;
			}
        }

        }
    else
    {
       cout << "error" << endl;
    }
	}
	}
}

Node& DoublyLinkedList::find(int val)
{
    //Node* front = new Node();
    Node* curr = new Node();
    curr = head;
	
	while(curr->next != nullptr) {
		if(curr->data == val) {
			return *curr;
		}
		curr = curr->next;
	}
	if(curr->data == val){
		return *curr;
	}
	
	throw runtime_error("error");
	
    /*for(int i = 0; curr->data != val; ++i)
            {
            //loop to the position
            front = curr;
            curr = curr->next;
            }
	if(curr->next == nullptr){
		throw runtime_error("error");
	}
	*/
}

void DoublyLinkedList::delete_at(int idx)
{
    Node* front = new Node();
    Node* curr = new Node();
	Node* temp = new Node();
	temp = head;
	
	int counter = 0;
	
    while(temp != nullptr) {
		counter++;
		temp = temp ->next;
	}
	
	if(counter < idx){
		
	throw runtime_error("error");
	
	}
		
	
	
    curr = head;
	int i = 0;


    if(head != NULL)
    {
        if(idx == 0){

            head = curr->next;
            curr->next->prev = nullptr;
        }
        else{

            while(curr->next != NULL && i != idx  )
            {
            //loop to the position
            front = curr;
            curr = curr->next;
			++i;
            }
            if(curr == tail){
                tail = curr->prev;
                curr->prev->next = nullptr;
            }
			else if(i+1 == idx){
				
			}
			else if(i !=idx){
				
				throw runtime_error("error");
			}
            else{
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