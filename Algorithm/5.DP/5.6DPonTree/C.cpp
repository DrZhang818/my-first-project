#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/28258/C
int n;
void solve() {
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n; i++) {
        int u, sz;
        scanf("%d:(%d)", &u, &sz);
        u++;
        for(int j = 1; j <= sz; j++) {
            int v;
            scanf("%d", &v);
            v++;
            adj[u].push_back(v);
            adj[v].push_back(u);            
        }
    }
    vector<array<int,2>> dp(n + 1);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        dp[u][1] = 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            dp[u][0] += dp[v][1];
            dp[u][1] += min(dp[v][0], dp[v][1]);
        }
    };
    dfs(dfs, 1, 0);
    printf("%d\n", min(dp[1][0], dp[1][1]));
}

int main() {

    while(cin >> n) {
        solve();
    }
    return 0;
}
