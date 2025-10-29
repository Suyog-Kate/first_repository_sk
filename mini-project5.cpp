#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii;

void printPath(vector<int> &parent, int j) {
    if (parent[j] == -1) {
        cout << j;
        return;
    }
    printPath(parent, parent[j]);
    cout << " -> " << j;
}

void dijkstra(int V, vector<vector<pii>> &adj, int src) {
    vector<int> dist(V, numeric_limits<int>::max());
    vector<int> parent(V, -1);

    dist[src] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int currDist = pq.top().first;
        pq.pop();

        if (currDist > dist[u])
            continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nVertex\tDistance\tPath from source " << src << "\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t";
        if (dist[i] == numeric_limits<int>::max()) {
            cout << "INF\t\t-\n";
        } else {
            cout << dist[i] << "\t\t";
            printPath(parent, i);
            cout << "\n";
        }
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<pii>> adj(V);

    cout << "Enter edges in format: u v w\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // For undirected graph; remove for directed
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    dijkstra(V, adj, source);

    return 0;
}
