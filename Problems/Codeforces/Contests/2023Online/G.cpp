#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

vector<int> fa, sz;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
    sz[u] += sz[v];
}
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1; 
    }
    return res;
}
void solve() {
    int n;
    cin >> n;
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    sz.resize(n + 1, 1);
    vector<PII> e(n - 1);
    for(int i = 0; i < n - 1; i++) {
        cin >> e[i].first >> e[i].second;
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> id(n + 1);
    iota(id.begin(), id.end(), 0);
    vector<vector<int>> nadj(n + 1);
    for(int i = 1; i <= n; i++) {
        nadj[i].push_back(i);
    }
    bool ok = true;
    int tot = 1;
    for(auto [u, v] : e) {
        u = find(u);
        v = find(v);
        if(sz[u] < sz[v]) {
            swap(u, v);
        }
        int cnt = 0;
        for(int o : nadj[v]) {
            for(int w : adj[o]) {
                if(id[w] == u) {
                    cnt++;
                }
            }
        }
        if(cnt != 1) {
            ok = false;
            break;
        }
        tot = 1LL * tot * sz[u] % MOD * sz[v] % MOD;
        merge(u, v);
        for(int o : nadj[v]) {
            nadj[u].push_back(o);
            id[o] = u;
        }
    }
    if(!ok) {
        cout << 0 << "\n";
        return;
    }
    cout << fast_pow(tot, MOD - 2) << "\n";
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
