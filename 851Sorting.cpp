#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

// so question is, basically have an array of 0, ... , n+1
// n is input, so if we input n=5, then we have an array of 0,1,2,3,4,5,6
// then we have a sequence of operations, up to n
// the operations is guaranteed that its from 1-n integers
// each operations is inserting a number
// print out the greatest number thats lower than the inserted number
// and the smalles number thats bigger than the inserted number

// e.g. n=5 | 1, 5, 2, 4, 3
// at the beggining the array always has 0, n+1
// insert 1 -> 0,1,6 | output = 1 6
// insert 5 -> 0,1,5,6 | output = 1 5
// etc



// approach is backwards so its o(n)
// so create list of permutations first. i.e. 0,1,2,3,4,5,6
// each node in list is doubly linked list node

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<Node*> llist(n + 2); 
        vector<int> operations(n);
        Node* prev = nullptr;

        for (int i = 0; i <= n + 1; i++) {
            Node* curr = new Node(i);
            if (prev != nullptr) {
                prev->next = curr;
                curr->prev = prev;
            }
            if (i > 0 && i <= n) {
                cin >> operations[i - 1];
            }
            prev = curr;
            llist[i] = curr;
        }

        vector<string> results;
        for (int i = n - 1; i >= 0; i--) {
            Node* curr = llist[operations[i]];
            Node* res1 = curr->prev;
            Node* res2 = curr->next;
            results.push_back(to_string(res1->data) + " " + to_string(res2->data));
            res1->next = res2;
            res2->prev = res1;
            delete curr;
        }

        // for (auto it = results.rbegin(); it != results.rend(); ++it) {
        //     cout << *it;
        // }
        for (int i=results.size()-1; i>=0; i--) {
            cout<<results[i]<<endl;
        }
    }
    return 0;
}