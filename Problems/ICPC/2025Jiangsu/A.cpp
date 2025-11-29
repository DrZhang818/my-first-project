#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = ll(1E18);

void solve() {
    int n, m, A, B;
    cin >> n >> m >> A >> B;
    vector<vector<int>> adj(1 << m);
    for(int i = 1; i <= n; i++) {
        int x = 0;
        for(int j = 0; j < m; j++) {
            char c;
            cin >> c;
            x |= (c - '0') << j;
        }
        adj[x].push_back(i);
    }
    vector<ll> k0(1 << m), b0(1 << m), k1(1 << m), b1(1 << m);
    for(int s = 0; s < 1 << m; s++) {
        int c = __builtin_popcount(s);
        ll sum = 0;
        for(int j = 0; j < m; j++) {
            if(s >> j & 1) {
                sum += j + 1;
            }
        }
        k0[s] = 1LL * A * c;
        b0[s] = B * sum;
        k1[s] = 1LL * A * (m - c);
        b1[s] = B * (1LL * m * (m + 1) / 2 - sum);
    }
    vector<vector<ll>> pre(1 << m);
    for(int s = 0; s < 1 << m; s++) {
        int sz = adj[s].size();
        if(sz == 0) continue;
        pre[s].resize(sz);
        pre[s][0] = adj[s][0];
        for(int j = 1; j < sz; j++) {
            pre[s][j] = pre[s][j - 1] + adj[s][j];
        }
    }

    ll ans = -inf;
    for(int s = 0; s < 1 << m; s++) {
        ll cur = 0;
        for(int x = 0; x < 1 << m; x++) {
            if(adj[x].size() == 0) continue;
            int sz = adj[x].size();
            int y = x ^ s;
            ll k = k1[y] - k0[y];
            ll b = b1[y] - b0[y];
            int l = -1, r = sz;
            while(l + 1 < r) {
                int mid = l + r >> 1;
                if(k * adj[x][mid] + b >= 0) {
                    if(k >= 0) {
                        r = mid;
                    } else {
                        l = mid;
                    }
                } else {
                    if(k >= 0) {
                        l = mid;
                    } else {
                        r = mid;
                    }
                }
            }
            int p = k >= 0 ? r : l;
            ll _pre, _suf;
            if(k >= 0) {
                _pre = p == 0 ? 0 : pre[x][p - 1];
                _suf = pre[x].back() - _pre;
            } else {
                _pre = p == -1 ? 0 : pre[x][p];
                _suf = pre[x].back() - _pre;
            }
            if(k >= 0) {
                cur += k0[y] * _pre + b0[y] * p;
                cur += k1[y] * _suf + b1[y] * (sz - p);
            } else {
                cur += k1[y] * _pre + b1[y] * (p + 1);
                cur += k0[y] * _suf + b0[y] * (sz - p - 1);
            }
        }
        ans = max(ans, cur);
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
