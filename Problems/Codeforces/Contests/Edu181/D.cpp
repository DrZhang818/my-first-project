#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

struct info {
    int l, r;
    ll p, q;
};
struct node {
    int l;
    ll p;
};
ll fast_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<node>> adj(m + 1);
    vector<ll> pre(m + 1, 1);
    for(int i = 1; i <= n; i++) {
        int l, r;
        ll p, q;
        cin >> l >> r >> p >> q;
        ll cur = (q - p) * fast_pow(q, MOD - 2) % MOD;
        adj[r].push_back({l, cur});
    }
    vector<ll> dp(m + 1);
    dp[0] = 1;
    ll cur = 1;
    for(int i = 1; i <= m; i++) {
        for(auto [l, p] : adj[i]) {
            cur = cur * p % MOD;
        }
        pre[i] = cur;
        for(auto [l, p] : adj[i]) {
            dp[i] += dp[l - 1] * cur % MOD * fast_pow(p, MOD - 2) % MOD * (1 - p + MOD) % MOD * fast_pow(pre[l - 1], MOD - 2) % MOD;
            dp[i] %= MOD;
        }
    }
    cout << dp[m] << "\n";
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
