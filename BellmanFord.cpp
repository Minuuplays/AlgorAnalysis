#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void printGraph(vector<vector<pair<int, int>>> &graph, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Vertex : " << i << " -> ";
        int a = graph[i].size();
        for (int j = 0; j < a; j++) {
            cout << "(" << graph[i][j].first << ", " << graph[i][j].second << ") ";
        }
        cout << "\n";
    }
}

void bellmanFord(vector<vector<pair<int, int>>> &graph, int n, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    // Step 1: relax all edges, V-1 times
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;   // skip unreached vertex (avoid overflow)

            int a = graph[u].size();
            for (int j = 0; j < a; j++) {
                int v = graph[u][j].first;
                int w = graph[u][j].second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    // Step 2: one more pass to check for negative-weight cycles
    bool hasNegativeCycle = false;
    for (int u = 0; u < n; u++) {
        if (dist[u] == INT_MAX) continue;

        int a = graph[u].size();
        for (int j = 0; j < a; j++) {
            int v = graph[u][j].first;
            int w = graph[u][j].second;
            if (dist[u] + w < dist[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
        if (hasNegativeCycle) break;
    }

    if (hasNegativeCycle) {
        cout << "\nGraph contains a negative weight cycle. Distances are not reliable.\n";
        return;
    }

    cout << "\nShortest distances from vertex " << src << " (Bellman-Ford):\n";
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << " : " << dist[i] << "\n";
    }
}

int main() {
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }

    printGraph(graph, n);

    int src;
    cout << "\nEnter source vertex: ";
    cin >> src;

    bellmanFord(graph, n, src);

    return 0;
}