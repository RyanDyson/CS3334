#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void buildPostorder(
        const vector<int>& preorder, 
        const vector<int>& inorder, 
        unordered_map<int, int>& inorderMap, 
        int preStart, 
        int inStart, 
        int inEnd, 
        vector<int>& postorder
    ) {

    if (preStart >= preorder.size() || inStart > inEnd) {
        return;
    }

    int root = preorder[preStart];
    int rootIndex = inorderMap[root];
    buildPostorder(preorder, inorder, inorderMap, preStart + 1, inStart, rootIndex - 1, postorder);
    buildPostorder(preorder, inorder, inorderMap, preStart + rootIndex - inStart + 1, rootIndex + 1, inEnd, postorder);

    postorder.push_back(root);
}

vector<int> getPostorder(const vector<int>& preorder, const vector<int>& inorder) {
    vector<int> postorder;
    unordered_map<int, int> inorderMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }
    buildPostorder(preorder, inorder, inorderMap, 0, 0, inorder.size() - 1, postorder);
    return postorder;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> preorder(N), inorder(N);
        for (int i = 0; i < N; ++i) {
            cin >> preorder[i];
        }
        for (int i = 0; i < N; ++i) {
            cin >> inorder[i];
        }

        vector<int> postorder = getPostorder(preorder, inorder);
        for (int i = 0; i < postorder.size(); ++i) {
            cout << postorder[i] << (i < postorder.size() - 1 ? " " : "");
        }
        cout << endl;
    }
    return 0;
}