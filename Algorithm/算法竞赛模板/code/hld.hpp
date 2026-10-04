#pragma once
#include <bits/stdc++.h>
using namespace std;
struct HLD {
    int n, cur;
    vector<int> siz, top, dep, parent, in, out, seq;
    vector<vector<int>> adj;
    HLD() {
    }
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.assign(n + 1, 0);
        top.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        parent.assign(n + 1, 0);
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
        seq.assign(n + 1, 0);
        adj.assign(n + 1, {});
        cur = 1;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 1) {
        vector<int> order{root};
        parent[root] = 0;
        dep[root] = 0;
        cur = 1;
        for(int i = 0; i < int(order.size()); i++) {
            int u = order[i];
            if(parent[u]) {
                adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
            }
            for(int v : adj[u]) {
                parent[v] = u, dep[v] = dep[u] + 1, order.push_back(v);
            }
        }
        for(int i = int(order.size()) - 1; i >= 0; i--) {
            int u = order[i];
            siz[u] = 1;
            int best = -1;
            for(int j = 0; j < int(adj[u].size()); j++) {
                int v = adj[u][j];
                siz[u] += siz[v];
                if(best == -1 || siz[v] > siz[adj[u][best]]) {
                    best = j;
                }
            }
            if(best >= 0) {
                swap(adj[u][0], adj[u][best]);
            }
        }
        vector<int> stk{root};
        top[root] = root;
        while(!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            in[u] = cur;
            seq[cur++] = u;
            out[u] = in[u] + siz[u];
            for(int i = int(adj[u].size()) - 1; i >= 0; i--) {
                int v = adj[u][i];
                top[v] = i == 0 ? top[u] : v;
                stk.push_back(v);
            }
        }
    }
    int lca(int u, int v) const {
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) const {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int jump(int u, int k) const {
        if(dep[u] < k) {
            return 0;
        }
        int d = dep[u] - k;
        while(dep[top[u]] > d) {
            u = parent[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }
    bool isAnc(int u, int v) const {
        return in[u] <= in[v] && in[v] < out[u];
    }
    int rootedParent(int root, int u) const {
        if(root == u) {
            return u;
        }
        if(!isAnc(u, root)) {
            return parent[u];
        }
        auto it = upper_bound(adj[u].begin(), adj[u].end(), root,
                              [&](int x, int y) { return in[x] < in[y]; });
        return *prev(it);
    }
    int rootedSize(int root, int u) const {
        if(root == u) {
            return n;
        }
        if(!isAnc(u, root)) {
            return siz[u];
        }
        return n - siz[rootedParent(root, u)];
    }
    int rootedLca(int a, int b, int root) const {
        return lca(a, b) ^ lca(b, root) ^ lca(root, a);
    }
};
