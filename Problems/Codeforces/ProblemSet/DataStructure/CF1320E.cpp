#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

// [in[u], out[u] - 1] 是以u为根的子树的dfs序区间
struct HLD {
    int n;
    vector<int> siz, top, dep, parent, in;
    vector<vector<int>> adj;
    int cur;

    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        cur = 1;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 1) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = 0;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if(parent[u]) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        siz[u] = 1;
        for(auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if(siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        for(auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
    }
    int lca(int u, int v) {
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};

struct Info {
    int u, t, id;
    friend bool operator<(const Info& a, const Info& b) {
        if(a.t != b.t) {
            return a.t > b.t;
        }
        return a.id > b.id;
    }
};

void solve() {  
    int n;
    cin >> n;

    HLD tr(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tr.addEdge(u, v);
    }

    tr.work();

    auto& in = tr.in;

    vector<vector<int>> vt(n + 1);
    vector<bool> vis(n + 1);
    vector<pair<int,int>> best(n + 1, {inf, inf});

    int q;
    cin >> q;
    while(q--) {
        int k, m;
        cin >> k >> m;

        vector<int> st(k + 1), w(k + 1);
        vector<int> nodes;

        for(int i = 1; i <= k; i++) {
            cin >> st[i] >> w[i];
            nodes.push_back(st[i]);
        }

        vector<int> Q(m + 1);
        for(int i = 1; i <= m; i++) {
            cin >> Q[i];
            nodes.push_back(Q[i]);
        }

        auto cmp = [&](auto x, auto y) { return in[x] < in[y]; };

        sort(nodes.begin(), nodes.end(), cmp);

        int sz = nodes.size();
        for(int i = 0; i < sz - 1; i++) {
            nodes.push_back(tr.lca(nodes[i], nodes[i + 1]));
        }

        sort(nodes.begin(), nodes.end(), cmp);

        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        sz = nodes.size();

        for(int i = 0; i < sz - 1; i++) {
            int p = tr.lca(nodes[i], nodes[i + 1]);
            vt[p].push_back(nodes[i + 1]);
            vt[nodes[i + 1]].push_back(p);
        }

        priority_queue<Info> pq;

        for(int u : nodes) {
            best[u] = {inf, inf};
        }

        for(int i = 1; i <= k; i++) {
            best[st[i]] = {0, i};
            pq.emplace(st[i], 0, i);
        }

        while(!pq.empty()) {
            auto [u, t, id] = pq.top(); pq.pop();
            if(vis[u]) {
                continue;
            }
            vis[u] = true;
            for(int v : vt[u]) {
                int d = tr.dist(st[id], v);
                int nt = (d + w[id] - 1) / w[id];
                if(make_pair(nt, id) < best[v]) {
                    best[v] = {nt, id};
                    pq.emplace(v, nt, id);
                }
            }
        }

        for(int i = 1; i <= m; i++) {
            cout << best[Q[i]].second << " \n"[i == m];
        }

        for(int u : nodes) {
            vis[u] = false;
            vt[u].clear();
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
