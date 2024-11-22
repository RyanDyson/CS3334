#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct UnionFind {
    vector<int> parent, rank;

    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> heights(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> heights[i][j];
        }
    }

    int T;
    cin >> T;
    vector<int> waterLevels(T);
    for (int i = 0; i < T; ++i) {
        cin >> waterLevels[i];
    }

    vector<int> results(T);
    vector<vector<bool>> flooded(n, vector<bool>(m, true));
    UnionFind uf(n * m);

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int t = T - 1; t >= 0; --t) {
        int waterLevel = waterLevels[t];
        int islands = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (heights[i][j] > waterLevel && flooded[i][j]) {
                    flooded[i][j] = false;
                    islands++;
                    int cellIndex = i * m + j;

                    for (auto [di, dj] : directions) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && !flooded[ni][nj]) {
                            int neighborIndex = ni * m + nj;
                            if (uf.find(cellIndex) != uf.find(neighborIndex)) {
                                uf.unite(cellIndex, neighborIndex);
                                islands--;
                            }
                        }
                    }
                }
            }
        }

        results[t] = islands;
    }

    for (int i = 0; i < T; ++i) {
        cout << results[i] << " ";
    }
    cout << endl;

    return 0;
}