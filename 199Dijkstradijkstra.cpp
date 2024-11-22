#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int INF = INT_MAX;

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

vector<Edge> graph[MAXN];
int dist[MAXN], previous[MAXN];
bool used[MAXN][MAXN];

void clear_graph(int n) {
    for(int i = 0; i <= n; i++) {
        graph[i].clear();
    }
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            used[i][j] = false;
        }
    }
}

bool dijkstra(int n, int start, int end, vector<int>& path) {
    for(int i = 0; i <= n; i++) {
        dist[i] = INF;
        previous[i] = -1;
    }
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    
    while(!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if(d > dist[u]) continue;
        
        for(const Edge& e : graph[u]) {
            int v = e.to;
            int w = e.weight;
            
            if(used[u][v]) continue;
            
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                previous[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    
    if(dist[end] == INF) return false;
    
    path.clear();
    for(int curr = end; curr != -1; curr = previous[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());
    return true;
}

void solve() {
    int n;
    while(cin >> n && n) {
        clear_graph(n);
        int m;
        cin >> m;
        
        for(int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back(Edge(v, w));
            graph[v].push_back(Edge(u, w));
        }
        
        vector<int> path1;
        if(!dijkstra(n, 1, n, path1)) {
            cout << "Back to jail" << endl;
            continue;
        }
        
        int len1 = dist[n];
        
        for(int i = 0; i < path1.size()-1; i++) {
            int u = path1[i];
            int v = path1[i+1];
            used[u][v] = used[v][u] = true;
        }
        
        vector<int> path2;
        if(!dijkstra(n, 1, n, path2)) {
            cout << "Back to jail" << endl;
            continue;
        }
        
        int len2 = dist[n];
        cout << len1 + len2 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}