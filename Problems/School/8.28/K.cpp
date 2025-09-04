#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> A(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dp(n + 1);
    auto dfs1 = [&](auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            if(A[v] < A[u] && dp[v] == 0) {
                dp[u] = 1;
            }            
        }
    };
    dfs1(dfs1, 1, 0);
    A[0] = inf;
    auto dfs2 = [&](auto &&self, int u, int fa) -> void {
        if(A[fa] < A[u] && dp[fa] == false) {
            dp[u] = 1;
        }
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
        }
    };
    dfs2(dfs2, 1, 0);
    for(int i = 1; i <= n; i++) {
        if(dp[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
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
