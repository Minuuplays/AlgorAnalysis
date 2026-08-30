//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int b = INT_MAX;


void warshall(vector<vector<int>> &dist){
    int a = dist.size();

    for (int k=0;k<a;k++){
        for (int i=0;i<a;i++){
            for (int j=0;j<a;j++){
                if (dist[i][k]!=b && dist[k][j]!=b){
                    dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }

    for (const auto& row : dist)
    {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main(){
    int n,m;
    cin >> n >> m;

    //vector<vector<int>> dist;

    vector<vector<int>> dist(n, vector<int>(n, b));

    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if (i==j){
                dist[i][j]=0;
            }
        }
    }

    vector<vector<pair<int,int>>> graph(n);
    for (int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        graph[u].push_back({v,w});
        dist[u][v] = w;
    }


    warshall(dist);

    /*for(int i=0;i<n;i++){
        int a=graph[i].size();
        for(int j=0;j<a;j++){
            cout << graph[i][j].first << graph[i][j].second << endl;
        }
    }*/

 

    return 0;
}

