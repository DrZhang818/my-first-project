#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve() { 
    int n, Q;
    cin >> n >> Q;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vals(n + 1);
    while(Q--) {
        int u, x;
        cin >> u >> x;
        vals[u] += x;
    }
    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : adj[u]) {
            if(vis[v]) continue;
            vis[v] = true;
            vals[v] += vals[u];
            q.push(v);
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << vals[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
