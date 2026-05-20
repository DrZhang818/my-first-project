#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> a(m + 1), b(m + 1);
    vector<i64> s(m + 1), t(m + 1);
    vector<vector<int>> adj(n + 1);

    for(int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> s[i] >> t[i];
        adj[a[i]].push_back(i);
    }
    s[m] = t[m] = inf;

    for(int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), 
            [&](int x, int y) {
                return s[x] < s[y];
            });
    }

    vector<array<int,20>> dp(m + 1);

    for(int i = 0; i <= m; i++) {
        int v = b[i];
        auto it = lower_bound(adj[v].begin(), adj[v].end(), t[i], 
            [&](int id, i64 val) {
                return s[id] < val;
            });

        if(it != adj[v].end()) {
            dp[i][0] = *it;
        } else {
            dp[i][0] = m;
        }
    }

    for(int j = 1; j < 20; j++) {
        for(int i = 0; i <= m; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }

    while(q--) {
        i64 X, Z;
        int Y;
        cin >> X >> Y >> Z;

        auto it = lower_bound(adj[Y].begin(), adj[Y].end(), X, 
            [&](int id, i64 val) {
                return s[id] < val;
            });

        if(it == adj[Y].end() || s[*it] >= Z) {
            cout << Y << "\n";
            continue;
        }

        int cur = *it;
        for(int j = 19; j >= 0; j--) {
            if(s[dp[cur][j]] < Z) {
                cur = dp[cur][j];
            }
        }

        if(Z <= t[cur]) {
            cout << a[cur] << " " << b[cur] << "\n";
        } else {
            cout << b[cur] << "\n";
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
