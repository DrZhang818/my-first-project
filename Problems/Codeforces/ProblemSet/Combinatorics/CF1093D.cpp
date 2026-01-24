#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int power2[300005];

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
    auto cal = [&](int st) -> int {
        int c0 = 0, c1 = 0;
        queue<int> q;
        q.push(st);
        col[st] = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            if(col[u] == 0) {
                c0++;
            } else {
                c1++;
            }
            for(int v : adj[u]) {
                if(col[v] == col[u]) {
                    return 0;
                }
                if(col[v] == -1) {
                    col[v] = col[u] ^ 1;
                    q.push(v);
                }
            }
        }
        int res = 0;
        add(res, power2[c0]);
        add(res, power2[c1]);
        return res;
    };  
    int ans = 1;
    for(int u = 1; u <= n; u++) {
        if(col[u] == -1) {
            int prod = cal(u);
            ans = 1LL * ans * prod % MOD;
            if(ans == 0) {
                break;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    power2[0] = 1;
    for(int i = 1; i <= 300000; i++) {
        power2[i] = 2 * power2[i - 1] % MOD;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
