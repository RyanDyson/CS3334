#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 505;
const double EPS = 1e-9;

struct Edge {
    int u, v;
    double w;
};

vector<Edge> edges;
vector<vector<pair<int,int>>> adj;
int n, m;

void dfs(int v, const vector<bool>& edge_mask, vector<bool>& visited, int& vertices) {
    visited[v] = true;
    vertices++;
    
    for(auto& p : adj[v]) {
        int u = p.first;
        int edge_idx = p.second;
        if(!visited[u] && edge_mask[edge_idx]) {
            dfs(u, edge_mask, visited, vertices);
        }
    }
}

pair<double,int> find_component(vector<bool>& edge_mask, int start) {
    vector<bool> visited(n+1, false);
    int vertices = 0;
    double sum = 0;
    int edge_count = 0;
    
    // First count vertices in this component
    dfs(start, edge_mask, visited, vertices);
    
    // Calculate sum of weights for edges in this component
    for(int i = 0; i < m; i++) {
        if(edge_mask[i]) {
            if(visited[edges[i].u] && visited[edges[i].v]) {
                sum += edges[i].w;
                edge_count++;
            }
        }
    }
    
    if(edge_count == 0) return {-1e9, 0};
    return {sum/edge_count, vertices};
}

int solve() {
    if(n == 0 && m == 0) return -1;
    
    edges.clear();
    adj.clear();
    adj.resize(n+1);
    
    // Read edges
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, (double)w});
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    
    double max_avg = -1e9;
    int max_vertices = 0;
    
    // Try all possible subsets of edges using binary representation
    for(int mask = 1; mask < (1 << m); mask++) {
        vector<bool> edge_mask(m);
        for(int i = 0; i < m; i++) {
            edge_mask[i] = (mask & (1 << i)) != 0;
        }
        
        // Try each vertex as starting point
        for(int start = 1; start <= n; start++) {
            vector<bool> visited(n+1, false);
            bool is_start = false;
            
            // Check if start vertex is part of any selected edge
            for(int i = 0; i < m; i++) {
                if(edge_mask[i] && (edges[i].u == start || edges[i].v == start)) {
                    is_start = true;
                    break;
                }
            }
            
            if(!is_start) continue;
            
            pair<int,int> temp = find_component(edge_mask, start);
            
            if(temp.first > max_avg + EPS) {
                max_avg = temp.first;
                max_vertices = temp.second;
            } else if(abs(temp.first - max_avg) <= EPS) {
                max_vertices = max(max_vertices, temp.second);
            }
        }
    }
    
    return max_vertices;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while(cin >> n >> m) {
        int result = solve();
        if(result == -1) break;
        cout << result << "\n";
    }
    
    return 0;
}