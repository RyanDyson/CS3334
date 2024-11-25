#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int weight;
    int left, right;
};

vector<Node> tree;
int n;

// Calculate total distance from a specific node to all other nodes
long long calcTotalDist(int root) {
    vector<int> dist(n + 1, -1);  // -1 means not visited
    long long total = 0;
    queue<int> q;
    
    // BFS to calculate distances
    q.push(root);
    dist[root] = 0;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        // Add distance × weight for current node
        total += (long long)dist[curr] * tree[curr].weight;
        
        // Process left child
        if (tree[curr].left && dist[tree[curr].left] == -1) {
            dist[tree[curr].left] = dist[curr] + 1;
            q.push(tree[curr].left);
        }
        
        // Process right child
        if (tree[curr].right && dist[tree[curr].right] == -1) {
            dist[tree[curr].right] = dist[curr] + 1;
            q.push(tree[curr].right);
        }
        
        // Process parent (using adjacency info from children)
        for (int i = 1; i <= n; i++) {
            if ((tree[i].left == curr || tree[i].right == curr) && dist[i] == -1) {
                dist[i] = dist[curr] + 1;
                q.push(i);
            }
        }
    }
    
    return total;
}

int main() {
    cin >> n;
    tree.resize(n + 1);
    
    // Read input
    for (int i = 1; i <= n; i++) {
        cin >> tree[i].weight >> tree[i].left >> tree[i].right;
    }
    
    // Try each node as the concert location
    long long minDist = 1e18;
    for (int i = 1; i <= n; i++) {
        long long dist = calcTotalDist(i);
        minDist = min(minDist, dist);
        
        // Pruning: if distance starts increasing, we can stop
        // (based on the convex nature of the distance function)
        if (i > 1 && dist > minDist) {
            break;
        }
    }
    
    cout << minDist << endl;
    return 0;
}