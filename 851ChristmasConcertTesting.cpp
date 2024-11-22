#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct City {
    int audience;
    int left;
    int right;
};

vector<City> cities;
vector<vector<int>> adjList;
vector<int> audienceCount;
vector<int> subtreeSize;
vector<long long> distanceSum;

void buildTree(int n) {
    adjList.resize(n + 1);
    cities.resize(n + 1);
    audienceCount.resize(n + 1, 0);
    subtreeSize.resize(n + 1, 0);
    distanceSum.resize(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int audience, left, right;
        cin >> audience >> left >> right;
        cities[i] = {audience, left, right};
        audienceCount[i] = audience;
        if (left != 0) adjList[i].push_back(left);
        if (right != 0) adjList[i].push_back(right);
    }
}

void dfs(int node, int parent) {
    subtreeSize[node] = audienceCount[node];
    for (int neighbor : adjList[node]) {
        if (neighbor == parent) continue;
        dfs(neighbor, node);
        subtreeSize[node] += subtreeSize[neighbor];
        distanceSum[node] += distanceSum[neighbor] + subtreeSize[neighbor];
    }
}

void dfs2(int node, int parent, long long parentDistanceSum) {
    if (parent != 0) {
        distanceSum[node] = parentDistanceSum + (subtreeSize[0] - 2 * subtreeSize[node]);
    }
    for (int neighbor : adjList[node]) {
        if (neighbor == parent) continue;
        dfs2(neighbor, node, distanceSum[node]);
    }
}

int main() {
    int n;
    cin >> n;

    buildTree(n);

    dfs(1, 0);

    // Correct the initial distance sum for the root
    long long totalDistance = 0;
    for (int i = 1; i <= n; ++i) {
        totalDistance += distanceSum[i];
    }
    distanceSum[1] = totalDistance;

    dfs2(1, 0, totalDistance);

    long long minSum = LLONG_MAX;
    for (int i = 1; i <= n; ++i) {
        minSum = min(minSum, distanceSum[i]);
    }

    cout << minSum << endl;

    return 0;
}