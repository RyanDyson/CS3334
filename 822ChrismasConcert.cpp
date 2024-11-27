#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

class Graph {
public:
    int numCities;
    vector<int> audience;
    vector<vector<int>> adjList;
    vector<int> subtreeSize;
    vector<long long> distanceSum;

    Graph(int n) : numCities(n) {
        audience.resize(n + 1);
        adjList.resize(n + 1);
        subtreeSize.resize(n + 1, 0);
        distanceSum.resize(n + 1, 0);
    }

    void insert() {
        for (int i = 1; i <= numCities; i++) {
            int a, x, y;
            cin >> a >> x >> y;
            audience[i] = a;
            if (x != 0) {
                adjList[i].push_back(x);
                adjList[x].push_back(i);
            }
            if (y != 0) {
                adjList[i].push_back(y);
                adjList[y].push_back(i);
            }
        }
    }

    void dfs(int node, int parent) {
        subtreeSize[node] = audience[node];
        for (int neighbor : adjList[node]) {
            if (neighbor != parent) {
                dfs(neighbor, node);
                subtreeSize[node] += subtreeSize[neighbor];
                distanceSum[node] += distanceSum[neighbor] + subtreeSize[neighbor];
            }
        }
    }

    void dfs2(int node, int parent) {
        for (int neighbor : adjList[node]) {
            if (neighbor != parent) {
                distanceSum[neighbor] = distanceSum[node] + (subtreeSize[1] - 2 * subtreeSize[neighbor]);
                dfs2(neighbor, node);
            }
        }
    }

    long long findBestCity() {
        dfs(1, -1);
        dfs2(1, -1);
        return *min_element(distanceSum.begin() + 1, distanceSum.end());
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    Graph graph(n);
    graph.insert();

    // auto start = chrono::high_resolution_clock::now();
    long long result = graph.findBestCity();
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration = end - start;

    cout << result << endl;
    // cout << "Running time: " << duration.count() << " seconds" << endl;

    return 0;
}