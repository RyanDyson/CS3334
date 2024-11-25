#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Graph {
    public:
        int v;
        vector<vector<int>> adjacencyMatrix;

        Graph(int numNodes) {
            v = numNodes;
            adjacencyMatrix.resize(numNodes + 1);
        }

        void dfs(int v, vector<bool>& visited, set<int> &nodes) {
            visited[v] = true;
            nodes.insert(v);

            for (int u: adjacencyMatrix[v]) {
                if (!visited[u]) {
                    dfs(u, visited, nodes);
                }
            }
        }

        bool isTree(const set<int>& nodes) {
            int vertices = nodes.size();
            int e = 0;

            for (int v: nodes) {
                for (int u: adjacencyMatrix[v]) {
                    if (nodes.count(u)) {
                        e++;
                    }
                }
            }

            e /= 2;
            return e == (vertices - 1);
        }

        int countTrees() {
            vector<bool>* visited = new vector<bool>(this->v +1, false);
            vector<set<int>> nodes;

            for (int v=1; v<=this->v; v++) {
                if (!(*visited)[v]) {
                    set<int> nodesCurr;
                    dfs(v, *visited, nodesCurr);
                    nodes.push_back(nodesCurr);
                }
            }

            int treeCount = 0;
            for (const auto& node: nodes) {
                if (isTree(node)) {
                    treeCount++;
                }
            }

            return treeCount;
        }

        void addEdge(int v, int u) {
            adjacencyMatrix[v].push_back(u);
            adjacencyMatrix[u].push_back(v);
        }
};

int main() {
    int numNodes, numEdges;
    int caseNum = 1;
    while (cin>>numNodes>>numEdges) {
        if (numNodes == 0 && numEdges == 0) {
            break;
        }

        Graph manILoveDataStructure(numNodes);

        for (int i=0; i<numEdges; i++) {
            int v, u;
            cin>>v>>u;
            manILoveDataStructure.addEdge(v, u);
        }

        int treeCount = manILoveDataStructure.countTrees();
        switch(treeCount) {
            case 0:
                cout<<"Case "<<caseNum<<": No trees."<<endl;
                break;
            case 1:
                cout<<"Case "<<caseNum<<": There is one tree."<<endl;
                break;
            default:
                cout<<"Case "<<caseNum<<": A forest of "<<treeCount<<" trees."<<endl;
        }

        caseNum++;
    }
}

