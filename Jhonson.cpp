//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
int B =INT_MAX;

vector<int> dijkstra(vector<vector<pair<int,int>>> &g,int n,int src){

    vector <int> dist(n,B);
    vector <bool> visited(n,false);
    dist[src]=0;

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

        int a = g[u].size();
        for (int j = 0; j < a; j++) {
            int v = g[u][j].first;
            int w = g[u][j].second;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

bool bellmanFord(vector<vector<pair<int, int>>> &graph, int n, int src, vector<int> &dist) {
    dist.assign(n, B);
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;   
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

    return hasNegativeCycle;
}

void johnson(vector<vector<pair<int,int>>> &g, int n) {
    // Step 1: build g' = g plus source q (index n) with 0-weight edges to everyone
    vector<vector<pair<int,int>>> gPrime = g;
    gPrime.resize(n + 1);
    for (int i = 0; i < n; i++) {
        gPrime[n].push_back({i, 0});
    }

    // Step 2: Bellman-Ford from q gives h[v]
    vector<int> h;
    bool hasNegCycle = bellmanFord(gPrime, n + 1, n, h);
    if (hasNegCycle) {
        cout << "Graph contains a negative weight cycle.\n";
        return;
    }

    // Step 3: reweight every original edge
    vector<vector<pair<int,int>>> gReweighted(n);
    for (int u = 0; u < n; u++) {
        for (auto &e : g[u]) {
            int v = e.first, w = e.second;
            gReweighted[u].push_back({v, w + h[u] - h[v]});
        }
    }

    // Step 4: Dijkstra from every vertex, then un-reweight
    for (int u = 0; u < n; u++) {
        vector<int> dPrime = dijkstra(gReweighted, n, u);
        cout << "From vertex " << u << ":\n";
        for (int v = 0; v < n; v++) {
            if (dPrime[v] == B) {
                cout << "  to " << v << ": unreachable\n";
            } else {
                cout << "  to " << v << ": " << dPrime[v] - h[u] + h[v] << "\n";
            }
        }
    }
}

int main(){
    int n,m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> graph(n);
    for (int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        graph[u].push_back({v,w});
    }

    johnson(graph, n);


   /*for(int i=0;i<n;i++){
        int a=graph[i].size();
        for(int j=0;j<a;j++){
            cout << graph[i][j].first << graph[i][j].second << endl;
        }
    }*/

    return 0;
}