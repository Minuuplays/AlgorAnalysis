#include <iostream>
#include <vector>
//                      #include <bits/stdc++.h>
using namespace std;

// undirected weighted graph representation using adjacency list

int main() {
    int n,m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    
    for(int i=0; i<n ; i++) {
        cout << "Vertex : " << i << " -> ";
        int a = graph[i].size();
        for (int j=0; j<a; j++) {
            cout << "(" << graph[i][j].first << ", " << graph[i][j].second << ") ";
        }

    }

    return 0;
}