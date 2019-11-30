#include <iostream>
#include <stdexcept>
#include "Node.h"
#include "DoublyLinkedList.h"

using namespace std;

int main()
try {

    DoublyLinkedList ll;
    cout << ll << endl << endl;
    ll.insert_front(7);
    cout << ll << endl << endl;
    ll.insert_front(11);
    cout << ll << endl << endl;
    ll.insert_front(27);
    cout << ll << endl << endl;

    return 0;
}
catch(runtime_error& e){
    cerr << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "exception\n";
    return 2;
}