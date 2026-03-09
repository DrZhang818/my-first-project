#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, h;
    cin >> n >> h;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> lson(n + 1), rson(n + 1);
    vector<int> fa(n + 1);

    vector<int> pre(n + 1), suf(n + 1, n + 1);

    stack<int> stk;
    for(int i = 1; i <= n; i++) {
        int u = -1;
        while(!stk.empty() && a[i] >= a[stk.top()]) {
            u = stk.top();
            stk.pop();
            suf[u] = i;
        }
        if(u != -1) {
            fa[u] = i;
            lson[i] = u;
        }
        if(!stk.empty()) {
            pre[i] = stk.top();
            fa[i] = stk.top();
            rson[stk.top()] = i;
        }
        stk.push(i);
    }

    int rt = -1;
    while(!stk.empty()) {
        rt = stk.top();
        stk.pop();
    }

    vector<array<i64,3>> dp(n + 1);
    vector<i64> w(n + 1);

    auto dfs = [&](this auto&& self, int u) -> void {
        w[u] = u == rt ? 1LL * (h - a[u]) * n : 1LL * (a[fa[u]] - a[u]) * (suf[u] - pre[u] - 1);
        dp[u][1] = dp[u][2] = w[u];
        for(int v : {lson[u], rson[u]}) {
            if(v == 0) continue;
            self(v);
            dp[u][2] = max(dp[u][2], dp[v][2] + w[u]);
            dp[u][2] = max(dp[u][2], dp[u][1] + dp[v][1]);
            dp[u][1] = max(dp[u][1], dp[v][1] + w[u]);
        }
    };
    dfs(rt);

    cout << dp[rt][2] << "\n";
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
