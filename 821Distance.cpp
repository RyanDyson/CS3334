#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<long long, long long> pll;
vector<vector<pair<int, int>>> graph;
vector<bool> visited;

pll dfs(int start) {
    visited[start] = true;
    long long max_dist = 0;
    long long farthest_node = start;
    
    for(const auto& edge : graph[start]) {
        int next_node = edge.first;
        int weight = edge.second;
        
        if(!visited[next_node]) {
            pll result = dfs(next_node);
            long long dist = result.first + weight;
            if(dist > max_dist) {
                max_dist = dist;
                farthest_node = result.second;
            }
        }
    }
    
    return {max_dist, farthest_node};
}

long long find_longest_path(int n) {
    // First DFS from node 1
    visited.assign(n + 1, false);
    pll first_result = dfs(1);
    
    // Second DFS from the farthest node
    visited.assign(n + 1, false);
    pll second_result = dfs(first_result.second);
    
    return second_result.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    // Initialize graph
    graph.resize(n + 1);
    visited.resize(n + 1);
    
    // Read edges
    for(int i = 0; i < n-1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    
    cout << find_longest_path(n) << endl;
    
    return 0;
}