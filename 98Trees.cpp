#include <iostream>
#include <vector>
using namespace std;

class Node {
    public:
    int data;
    vector<Node*> next;

    Node() {
        data = 0 ;
    }
};

int main() {
    int nodeNum;
    while (cin>>nodeNum) {
        int operationNum; cin>>operationNum;
        Node** allTrees = new Node*[nodeNum];

        for (int i=0; i<operationNum; i++) {
            int node1; cin>>node1;
            int node2; cin>>node2;
        }
    }
    
}