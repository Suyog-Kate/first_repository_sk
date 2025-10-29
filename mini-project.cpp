// Mini Project: Graph Traversal Using BFS and DFS (C++)

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <set>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> adjList;
public:
    // Add an edge (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void bfs(int start) {
        set<int> visited;
        queue<int> q;
        q.push(start);
        visited.insert(start);

        cout << "BFS Traversal starting from node " << start << ": ";
        while (!q.empty()) {
            int node = q.front(); q.pop();
            cout << node << " ";

            for (int neighbor : adjList[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }

    void dfsUtil(int node, set<int>& visited) {
        visited.insert(node);
        cout << node << " ";

        for (int neighbor : adjList[node]) {
            if (visited.find(neighbor) == visited.end()) {
                dfsUtil(neighbor, visited);
            }
        }
    }

    void dfs(int start) {
        set<int> visited;
        cout << "DFS Traversal starting from node " << start << ": ";
        dfsUtil(start, visited);
        cout << "\n";
    }
};

int main() {
    Graph g;
    int nodes, edges;

    cout << "Enter number of nodes: ";
    cin >> nodes;

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (u v) pairs:\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int startNode;
    cout << "Enter starting node for traversal: ";
    cin >> startNode;

    g.bfs(startNode);
    g.dfs(startNode);

    return 0;
}
