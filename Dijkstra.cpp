#include <iostream>
#include <vector>
#include <queue>
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

void dijkstra(vector<vector<pair<int, int>>> &graph, int n, int src) {
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // greater is used to make it a min-heap ...flips the pq
    pq.push(make_pair(0, src)); // same as pq.push({0, src})

    while (!pq.empty()) {
        pair<int,int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (visited[u]) continue;      // already finalized, skip
        if (d > dist[u]) continue;     // stale entry, skip (lazy deletion)

        visited[u] = true;

        int a = graph[u].size();
        for (int j = 0; j < a; j++) {
            int v = graph[u][j].first;
            int w = graph[u][j].second;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "\nShortest distances from vertex " << src << ":\n";
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

    dijkstra(graph, n, src);

    return 0;
}