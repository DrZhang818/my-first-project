#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1970/problem/C2
void solve() {
    int n, t;
    cin >> n >> t;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<array<int,2>> dp(n + 1);
    vector<int> cnt(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        if(u != 1 && adj[u].size() == 1) {
            dp[u][0] = 1;
            dp[u][1] = 0;
            return;
        }
        dp[u][1] = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            if(dp[v][0]) {
                dp[u][1] = 1;
                cnt[u]++;
            }
        }
        dp[u][0] = dp[u][1] ^ 1;
    };
    dfs(1, 0);
    auto dfs2 = [&](this auto &&self, int u, int fa) -> void {
        if(fa) {
            if(cnt[fa] == 0 || cnt[fa] == 1 && dp[u][0] == 1) {
                dp[u][1] = 1;
                cnt[u]++;
            }
        }
        dp[u][0] = dp[u][1] ^ 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
        }
    };
    dfs2(1, 0);
    for(int i = 1; i <= t; i++) {
        int u;
        cin >> u;
        if(dp[u][1]) {
            cout << "Ron\n"; 
        } else {
            cout << "Hermione\n";
        }
    }
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
