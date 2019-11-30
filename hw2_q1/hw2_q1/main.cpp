#include <iostream>
#include <queue>
using namespace std;

void pushS(queue<int>&q1, queue<int>&q2, int data){ // push function for stack
    if (q2.empty()) { // Firstly, insert data to q2 if q2 is empty regardless q1.
        q2.push(data); // stack
        cout << "No enqueue in q1, enqueue to q2.   --- ";
    }else{
        q1.push(data); //when q2 is not empty
        cout << "Enqueue q1: " << q1.front() << " --- "; // show the data which is inserted to q1
        while (!q2.empty()) { // *** move data in q2 to q1 one by one from front of q2
            q1.push(q2.front());
            q2.pop();
        }
        // Running time: O(n)
        // now q1 is contained data from q2, q2 is empty.
        swap(q1, q2); // Stack still equals to q2.
        if (q1.empty()) { // check if q1 is empty after called the function
            cout << "q1 is empty now. --- ";
        }
    }
}

int popS(queue<int>&q2){ // pop function for stack
    int r = q2.front();
    q2.pop();
    return r;
    //Running time: O(1)
}

int main() {
    queue<int>q1;
    queue<int>q2;
    
    cout << "Call push 5 times: " << endl;
    for (int i = 0; i < 5; i++) { // pushS
        pushS(q1, q2, i);
        queue<int>q3 = q2;
        cout << "q2, Stack: ";
        while(!q3.empty()) { // q3 is just used for showing current data in q2
            cout << q3.front() << " ";
            q3.pop();
        }
        cout << endl;
    }
    cout << endl << "Call popS 5 times, show Stack: " << endl;
    
    while (!q2.empty()) { // popS
        popS(q2);
        queue<int>q3 = q2; // q3 is just used for showing current data in q2
        while (!q3.empty()) {
            cout << q3.front() << " ";
            popS(q3);
        }
        if (q2.empty()) {
            cout << "empty" << endl;
        }
        cout << endl;
    }
}
