#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> col(n + 1, -1);
    queue<int> q;
    q.push(1);
    col[1] = 0;

    bool ok = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(col[v] == -1) {
                col[v] = col[u] ^ 1;
                q.push(v);
            } else if(col[v] != (col[u] ^ 1)) {
                ok = false;
                break;
            }
        }
    }

    if(!ok) {
        ll ans = 1LL * n * (n - 1) / 2 - m;
        cout << ans << "\n";
        return;
    }

    int c0 = 0, c1 = 0;
    for(int i = 1; i <= n; i++) {
        if(col[i] == 0) {
            c0++;
        } else {
            c1++;
        }
    }

    ll ans = 1LL * c0 * c1 - m;
    cout << ans << "\n";

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
