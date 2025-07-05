#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 100003;
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
    vector<int> d(n + 1, inf);
    vector<int> cnt(n + 1);
    d[1] = 0;
    cnt[1] = 1;
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                cnt[v] = cnt[u];
                q.push(v);
            } else if(d[v] == d[u] + 1) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << cnt[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
