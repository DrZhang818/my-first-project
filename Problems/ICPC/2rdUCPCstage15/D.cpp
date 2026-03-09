#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

constexpr int MOD = 998244353;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<set<int>> adj0(n + 1), adj1(n + 1);

    for(int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        if(c == 0) {
            adj0[u].insert(v);
            adj0[v].insert(u);
        } else {
            adj1[u].insert(v);
            adj1[v].insert(u);
        }
    }

    vector<int> to(n + 1);

    vector<int> vis(n + 1);
    int ans = n;
    for(int u = 1; u <= n; u++) {
        for(int v : adj0[u]) {
            if(v < u) continue;
            if(!adj1[u].contains(v)) continue;
            ans++;
            to[u] = v;
            to[v] = u;
            for(int x : adj0[u]) {
                if(x == v) continue;
                if(adj1[v].contains(x)) {
                    ans++;
                }
                if(to[x]) {
                    int y = to[x];
                    if(adj1[v].contains(y)) {
                        ans++;
                    }
                }
            }
            for(int x : adj1[u]) {
                if(x == v) continue;
                if(adj0[v].contains(x)) {
                    ans++;
                }
                if(to[x]) {
                    int y = to[x];
                    if(adj0[v].contains(y)) {
                        ans++;
                    }
                }
            }
        }

        if(vis[u]) continue;
        vector<int> vec;
        int c0 = 0, c1 = 0;
        for(int v : adj0[u]) {
            vec.push_back(v);
            c0++;
        }
        for(int v : adj1[u]) {
            vec.push_back(v);
            c1++;
        }
        if(c0 == 3 || c1 == 3 || c0 + c1 != 3 || vec[0] == vec[1] || vec[1] == vec[2] || vec[0] == vec[2]) {
            continue;
        }

        int x = vec[0], y = vec[1], z = vec[2];
        vis[u] = vis[x] = vis[y] = vis[z] = true;

        if(c0 == 1) {
            if(!adj0[y].contains(z)) {
                continue;
            }
            if(adj0[x].contains(y) && adj1[x].contains(z)) {
                ans++;
            }
            if(adj1[x].contains(y) && adj0[x].contains(z)) {
                ans++;
            }
        } else {
            if(!adj1[x].contains(y)) {
                continue;
            }
            if(adj0[z].contains(x) && adj1[z].contains(y)) {
                ans++;
            }
            if(adj1[z].contains(x) && adj0[z].contains(y)) {
                ans++;
            }
        }
        ans %= MOD;
    }

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
