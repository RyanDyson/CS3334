#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
public:
    int numCities;
    vector<vector<pair<int, int>>> adjList;  
    vector<bool> visited;
    int maxProfit;

    Graph(int n) {
        numCities = n;
        adjList.resize(n + 1);
        visited.resize(n + 1, false);
        maxProfit = -2147483648;
    }

    void addRoad(int city1, int city2, int profit) {
        adjList[city1].push_back({city2, profit});
        adjList[city2].push_back({city1, profit});
        maxProfit = max(maxProfit, profit);
    }

    void inputRoads(int m) {
        for (int i = 0; i < m; i++) {
            int city1, city2, profit;
            cin >> city1 >> city2 >> profit;
            addRoad(city1, city2, profit);
        }
    }

    int dfs(int currentCity) {
        int count = 1;
        
        for (const auto& road : adjList[currentCity]) {
            int nextCity = road.first;
            int profit = road.second;
            
            if (!visited[nextCity] && profit == maxProfit) {
                visited[nextCity] = true;
                count += dfs(nextCity);
            }
        }
        return count;
    }

    int findLargestComponent() {
        int maxCities = 0;
        fill(visited.begin(), visited.end(), false);

        for (int city = 1; city <= numCities; city++) {
            if (!visited[city]) {
                visited[city] = true;
                maxCities = max(maxCities, dfs(city));
            }
        }
        return maxCities;
    }

    void reset(int n) {
        numCities = n;
        adjList.clear();
        adjList.resize(n + 1);
        visited.clear();
        visited.resize(n + 1, false);
        maxProfit = -2147483648;
    }
};

int main() {
    int n, m;
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        Graph graph(n);
        graph.inputRoads(m);
        cout << graph.findLargestComponent() << endl;
    }
    return 0;
}