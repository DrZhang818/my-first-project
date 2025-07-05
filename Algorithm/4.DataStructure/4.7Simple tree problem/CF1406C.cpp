#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1406/C

void solve() { 
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int x = -1, y = -1;
    vector<int> siz(n, 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        int mx = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            dfs(v, u);
            siz[u] += siz[v];
            mx = max(mx, siz[v]);
        }
        if(max(mx, n - siz[u]) <= n / 2) {
            if(x == -1) {
                x = u;
            } else {
                y = u;
            }
        }
    };
    dfs(0, -1);
    if(y == -1) {
        cout << x + 1 << " " << adj[x][0] + 1 << "\n";
        cout << x + 1 << " " << adj[x][0] + 1 << "\n";
        return;
    }
    int p;
    for(int v : adj[y]) {
        if(v != x) {
            p = v;
            break;
        }
    }
    cout << y + 1 << " " << p + 1 << "\n";
    cout << x + 1 << " " << p + 1 << "\n";
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
    
