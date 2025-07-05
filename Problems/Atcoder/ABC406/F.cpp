#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const int inf = 1000000000;

int n;
struct info {
    int u, v;
};
inline int lowbit(int o) { return o & -o; }
vector<ll> tr;
void add(int o, int d) {
    for(; o <= n; o += lowbit(o)) {
        tr[o] += d;
    }
}
ll query(int o) {
    ll res = 0;
    for(; o > 0; o -= lowbit(o)) {
        res += tr[o];
    }
    return res;
}
void solve() {
    int timer = 0;
    cin >> n;
    tr.resize(n + 1);
    vector<vector<int>> adj(n + 1);
    vector<int> L(n + 1), R(n + 1);
    vector<info> e(n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        e[i] = {u, v};
    }
    auto dfs = [&](auto && dfs, int u, int fa) -> void {
        L[u] = ++timer;
        for(int v : adj[u]) {
            if(v == fa) continue;
            dfs(dfs, v, u);
        }
        R[u] = timer;
    };
    dfs(dfs, 1, 0);
    for(int i = 1; i <= n; i++) add(i, 1);
    int q;
    cin >> q;
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int o, d;
            cin >> o >> d;
            add(L[o], d);
        } else {
            int i;
            cin >> i;
            auto [u, v] = e[i];
            if(L[u] < L[v]) swap(u, v);
            ll tot = query(n), w = query(R[u]) - query(L[u] - 1);
            cout << abs(tot - 2 * w) << "\n";
        }
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}