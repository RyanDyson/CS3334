#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    bool shouldCut = false;
    bool shouldKeep = false;
    int data;
    unordered_map<int, Node*> children;

    Node() {
        shouldCut = false;
        shouldKeep = false;
        data = 0;
    }
    Node(int d) {
        shouldCut = false;
        shouldKeep = false;
        data = d;
    }
};

pair<bool,int> countCutOp(Node* node) {
    if (node->shouldKeep) { 
        return make_pair(false, 0); // Keep this node, no cuts needed
    }
    if (node->shouldCut) {
        return make_pair(true, 1); // Cut this node
    }

    int totalChildCuts = 0;
    bool allChildrenCuttable = true;

    for (auto& child : node->children) {
        pair<bool, int> childCuts = countCutOp(child.second);
        totalChildCuts += childCuts.second;
        if (childCuts.first == false) { 
            allChildrenCuttable = false;
        }
    }

    if (allChildrenCuttable) {
        return make_pair(true, 1); 
    } 

    return make_pair(false, totalChildCuts);
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;

    while (t--) {
        int n, m; cin>>n>>m;

        Node* root = new Node();
        while (n--) {
            Node* node = root;
            int branch = 0;
            while (branch != -1) {
                cin>>branch;
                if (branch == -1) {
                    break;
                }
                if (node->children[branch] == NULL) {
                    node->children[branch] = new Node(branch);
                }
                node = node->children[branch];
            }
            node->shouldCut = true;
        }

        while (m--) {
            Node* node = root;
            int branch = 0;
            while (branch != -1) {
                cin>>branch;
                if (branch == -1) {
                    break;
                }
                if (node->children[branch] == NULL) {
                    node->children[branch] = new Node(branch);
                }
                node = node->children[branch];
            }
            node->shouldKeep = true;
        }

        int totalCount = 0;
        for (auto& child : root->children) {
            pair<bool, int> currOpp = countCutOp(child.second);
            totalCount += currOpp.second;
        }

        cout << totalCount << endl;

    }
}