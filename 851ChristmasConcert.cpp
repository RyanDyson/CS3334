#include <iostream>
#include <vector>
using namespace std;

class Tree {
    public:
    int data;
    Tree* left;
    Tree* right;
};

int main() {
    int n; cin>>n;

    vector<Tree*> allNodes = vector<Tree*>(n);
    int i = n;
    while(i--) {
        int w, l, r;
        cin>>w>>l>>r;

        Tree* currCity = new Tree();
        currCity->data = w;
        currCity->left = allNodes[l-1];
        currCity->right = allNodes[r-1];
    }

    
}