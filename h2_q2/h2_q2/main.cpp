#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *next = nullptr;
};

class List{
public:
    Node *head = nullptr;
    Node *tail = nullptr;
    
    void makelist(int dta){
        Node *temp = new Node;
        temp->data = dta;
        if (head == nullptr) {
            head = temp;
            tail = temp;
            temp = nullptr;
        }else{
            tail->next = temp;
            tail = tail->next;
        }
    }
};

int countL(Node *head){ // recursion
    if (head == nullptr) {
        return 0;
    }
    return 1 + countL(head->next);
}
int countLL(Node *head1){ //iteration methods, running time: O(n)
    int count = 0;
    while (head1 != nullptr) {
        count++;
        head1 = head1->next;
    }
    return count;
}

int main() {
    List list;
    List list2;
    for (int i = 5; i >= 0; i--) {
        list.makelist(i);
    }
    for (int i = 0; i < 5; i++) {
        list2.makelist(i);
    }
    cout << "List1: " << countL(list.head) << endl;
    cout << "List2: " << countL(list2.head) << endl;
}
