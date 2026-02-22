#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;
constexpr int N = 18;

using pii = pair<int,int>;

void solve() {  
    int n;
    cin >> n;

    vector<array<int,N>> fa(n + 1);
    vector<array<int,N>> rmq(n + 1);

    for(int i = 0; i <= n; i++) {
        fill(rmq[i].begin(), rmq[i].end(), inf);
    }

    vector<vector<pii>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int cur = 1;
    vector<int> in(n + 1);
    vector<int> dep(n + 1);
    [&](this auto&& self, int u, int p) -> void {
        in[u] = cur++;
        dep[u] = dep[p] + 1;
        fa[u][0] = p;
        for(auto [v, w] : adj[u]) {
            if(v == p) continue;
            rmq[v][0] = w;
            self(v, u);
        }
    }(1, 0);

    for(int s = 1; s < N; s++) {
        for(int i = 1; i <= n; i++) {
            fa[i][s] = fa[fa[i][s - 1]][s - 1];
            rmq[i][s] = min(rmq[i][s - 1], rmq[fa[i][s - 1]][s - 1]);
        }
    }

    auto LCA = [&](int x, int y) {
        if(dep[x] < dep[y]) swap(x, y);
        for(int s = N - 1; s >= 0; s--) if(dep[fa[x][s]] >= dep[y]) x = fa[x][s];
        if(x == y) return x;
        for(int s = N - 1; s >= 0; s--) if(fa[x][s] != fa[y][s]) x = fa[x][s], y = fa[y][s];
        return fa[x][0]; 
    };

    auto get = [&](int u, int v) {
        int res = 1E9;
        for(int s = N - 1; s >= 0; s--) {
            if(dep[fa[v][s]] >= dep[u]) {
                res = min(res, rmq[v][s]);
                v = fa[v][s];
            }
        }
        return res;
    };

    vector<vector<int>> vt(n + 1);
    vector<i64> dp(n + 1, inf);
    vector<bool> tag(n + 1);

    int q;
    cin >> q;
    while(q--) {
        int k;
        cin >> k;
        vector<int> Q(k + 1);
        vector<int> nodes {1};
        nodes.reserve(k);
        for(int i = 1; i <= k; i++) {
            cin >> Q[i];
            nodes.push_back(Q[i]);
            tag[Q[i]] = true;
        }

        auto cmp = [&](auto x, auto y) { return in[x] < in[y]; };
        sort(nodes.begin(), nodes.end(), cmp);

        int sz = nodes.size();
        for(int i = 0; i < sz - 1; i++) {
            nodes.push_back(LCA(nodes[i], nodes[i + 1]));
        }

        sort(nodes.begin(), nodes.end(), cmp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        sz = nodes.size();

        for(int i = 0; i < sz - 1; i++) {
            int lca = LCA(nodes[i], nodes[i + 1]);
            vt[lca].push_back(nodes[i + 1]);
            vt[nodes[i + 1]].push_back(lca);
        }

        auto dfs = [&](this auto&& self, int u, int fa) -> void {
            if(tag[u]) return;
            dp[u] = 0;
            for(int v : vt[u]) {
                if(v == fa) continue;
                self(v, u);
                dp[u] += min(dp[v], i64(get(u, v)));
            }
        };
        dfs(1, 0);

        cout << dp[1] << "\n";

        for(int u : nodes) {
            vt[u].clear();
            dp[u] = inf;
            tag[u] = false;
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
