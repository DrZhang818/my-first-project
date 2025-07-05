#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, a, b, na, nb;
    cin >> n >> a >> b >> na >> nb;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if(nb <= 2 * na) {
        cout << "Alice\n";
        return;
    }
    int d = 0;
    auto dfs = [&](this auto &&self, int u, int fa) -> int {
        int mx = 0, se = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            int cur = self(v, u) + 1;
            if(cur >= mx) {
                se = mx;
                mx = cur;
            } else if(cur > se) {
                se = cur;
            }
        }
        d = max(d, mx + se);
        return mx;
    };
    int dist = 0;
    queue<int> q;
    q.push(a);
    vector<bool> vis(n + 1, false);
    vis[a] = true;
    while(!q.empty()) {
        bool ok = false;
        for(int i = 0, j = q.size(); i < j; i++) {
            int u = q.front(); q.pop();
            if(u == b) {
                ok = true;
                break;
            }
            for(int v : adj[u]) {
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        if(ok) break;
        dist++;
    }
    if(dist <= na) {
        cout << "Alice\n";
        return;
    }
    dfs(1, 0);
    if(d > 2 * na) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
