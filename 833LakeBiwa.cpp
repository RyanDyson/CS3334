#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Cell {
    public:
        int height, idx, idy;

        Cell() {
            height = 0;
            idx = 0;
            idy = 0;
        }

        Cell(int h, int i, int j) {
            height = h;
            idx = i;
            idy = j;
        }

        bool operator<(const Cell& other) const {
            return height > other.height;
        }
};

class Water {
    public:
        int height, originalIdx;

        Water() {
            height = 0;
            originalIdx = 0;
        }

        Water(int h, int i) {
            height = h;
            originalIdx = i;
        }

        bool operator<(const Water& other) const {
            return height > other.height;
        }
};

int find(int x, int* parent) {
    if (parent[x] != x) {
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}

void unionSet(int x, int y, int* parent, int* rank) {
    int px = find(x, parent);
    int py = find(y, parent);

    if (px == py) {
        return;
    }
    if (rank[px] < rank[py]) {
        swap(px, py);
    }
    parent[py] = px;
    if (rank[px] == rank[py]) {
        rank[px]++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin>>n>>m;
    vector<Cell> cells;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int h; cin>>h;
            cells.push_back(Cell(h, i, j));
        }
    }
    sort(cells.begin(), cells.end());

    int t; cin>>t;
    vector<Water> waterRise(t);
    for (int i=0; i<t; i++) {
        int h; cin>>h;
        waterRise[i] = Water(h, i);
    }
    sort(waterRise.begin(), waterRise.end());

    int* parent = new int[n*m];
    int* rank = new int[n*m];
    bool* aboveWater = new bool[n*m];

    for (int i=0; i<n*m; i++) {
        parent[i] = i;
        rank[i] = 0;
        aboveWater[i] = false;
    }

    int cellIdx = 0;
    int islands = 0;
    const int adjacentRow[] = {-1, 1, 0, 0};
    const int adjacentCol[] = {0, 0, -1, 1};

    vector<int> result(t);

    for (const Water& w: waterRise) {
        while (cellIdx < cells.size() && cells[cellIdx].height > w.height) {
            int r = cells[cellIdx].idx;
            int c = cells[cellIdx].idy;
            int idx = r*m + c;
            aboveWater[idx] = true;
            islands++;

            for (int i=0; i<4; i++) {
                int newR = r + adjacentRow[i];
                int newC = c + adjacentCol[i];
                if (newR >= 0 && newR < n && newC >= 0 && newC < m) {
                    int newIdx = newR*m + newC;
                    if (aboveWater[newIdx] && find(idx, parent) != find(newIdx, parent)) {
                        unionSet(idx, newIdx, parent, rank);
                        islands--;
                    }
                }
            }
            cellIdx++;
        }
        result[w.originalIdx] = islands;
    }

    for (int i = 0; i < t; i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout<<endl;

    delete[] parent;
    delete[] rank;
    delete[] aboveWater;
}