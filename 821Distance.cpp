#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<long long, long long> pll;

class Graph {
    public:
        int size;
        vector<vector<pair<int ,int>>> adjList;
        vector<bool> visitedList;

        Graph(int n) {
            size = n;
            adjList.resize(n+1);
        }

        void input() {
            for (int i=0; i<size-1; i++) {
                int u, v, w; cin>>u>>v>>w;
                adjList[u].push_back(make_pair(v, w));
                adjList[v].push_back(make_pair(u, w));
            }
        }

        void resize(int n) {
            adjList.resize(n);
        }
        
        pll dfs(int start);

        long long findDiameter(int n);
};


pll Graph::dfs(int start) {
    visitedList[start] = true;
    long long max_dist = 0;
    long long farthest_node = start;

    for(const auto& edge : adjList[start]) {
        int next_node = edge.first;
        int weight = edge.second;

        if(!visitedList[next_node]) {
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

long long Graph::findDiameter(int n) {
    visitedList.assign(n + 1, false);
    pll first = dfs(1);

    visitedList.assign(n + 1, false);
    pll second = dfs(first.second);

    return second.first;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin>>n;
    Graph graph(n);
    graph.input();

    cout << graph.findDiameter(n) << endl;
}