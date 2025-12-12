#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct info {
    int v, w;
};

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<info>> adj(n + 1):
    for(int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<int> ord(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> ord[i];
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
