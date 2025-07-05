#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> path;
    int sz = 1000000000, idx = -1;
    auto bfs = [&](int fa) -> void {
        queue<int> q;
        vector<bool> vis(n + 1, false);
        q.push(fa);
        bool ok = false;
        int cnt = 0;
        vis[fa] = true;
        while(!q.empty() && !ok) {
            int len = q.size();
            cnt++;
            while(len--) {
                int u = q.front();
                q.pop();
                for(int v : adj[u]) {
                    if(v == fa) {
                        ok = true;
                        if(cnt < sz) {
                            sz = cnt;
                            idx = fa;
                        }
                        return;
                    }
                    if(vis[v]) continue;
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    };
    auto work = [&](int fa) -> void {
        vector<int> pre(n + 1);
        vector<bool> vis(n + 1, false);
        queue<int> q;
        q.push(fa);
        vis[fa] = true;
        while(!q.empty()) {
            int len = q.size();
            while(len--) {
                int u = q.front();
                q.pop();   
                for(int v : adj[u]) {
                    if(v == fa) {
                        path.push_back(fa);
                        while(u != fa) {
                            path.push_back(u);
                            u = pre[u];
                        }
                        return;
                    }
                    if(vis[v]) continue;
                    pre[v] = u;
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        bfs(i);
    } 
    if(idx == -1) {
        cout << -1 << "\n";
    } else {
        work(idx);
        cout << path.size() << "\n";
        for(int i = 0; i < path.size(); i++) {
            cout << path[i] << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
