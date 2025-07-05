#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
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
    auto dfs = [&](auto &&dfs, int u, int fa) -> void {
        int mx = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            dfs(dfs, v, u);
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
    dfs(dfs, 0, -1);
    if(y != -1) x = x < y ? x : y;
    int sum = 0;
    auto go = [&](auto &&go, int u, int fa, int cnt) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            sum += cnt;
            go(go, v, u, cnt + 1);
        }
    };
    go(go, x, -1, 1);
    cout << x + 1 << " " << sum << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
