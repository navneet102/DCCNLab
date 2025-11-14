#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, e;
    cin >> n >> e;
 
    vector<vector<pair<int,int>>> g(n);
 
    for(int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});   // Undirected graph
    }
 
    int src;
    cin >> src;
 
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
 
    priority_queue<pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>> pq;
 
    pq.push({0, src});
 
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
 
        if(d != dist[u]) continue;
 
        for(auto [v, w] : g[u]) {
            if(dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
 
    for(int i = 0; i < n; i++)
        cout << "Shortest distance to node "
             << i << " = " << dist[i] << endl;
}