#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct HLD {
    int n;
    vector<int> siz, parent;
    vector<vector<int>> adj;

    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        parent.resize(n);
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 1) {
        parent[root] = 0;
        dfs(root);
    }
    void dfs(int u) {
        if(parent[u]) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        siz[u] = 1;
        for(auto &v : adj[u]) {
            parent[v] = u;
            dfs(v);
            siz[u] += siz[v];
            if(siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    }
};

class Solution {
public:
    ll interactionCosts(int n, vector<vector<int>>& e, vector<int>& bel) {
        HLD tr(n + 1);
        for(int i = 0; i < n - 1; i++) {
            int u = e[i][0] + 1, v = e[i][1] + 1;
            tr.addEdge(u, v);
        }
        tr.work();
        auto &adj = tr.adj;
        vector<int> cnt(21);
        vector<int> tot(21);
        for(int i = 0; i < n; i++) {
            tot[bel[i]]++;
        }
        ll ans = 0, cur = 0;
        auto add = [&](this auto &&self, int u, int x) -> void {
            int col = bel[u - 1];
            cur -= 1LL * cnt[col] * (tot[col] - cnt[col]);
            cnt[bel[u - 1]] += x;
            cur += 1LL * cnt[col] * (tot[col] - cnt[col]);
            for(int v : adj[u]) {
                self(v, x);
            }            
        };
        auto dfs = [&](this auto &&self, int u, bool del) -> void {
            for(int i = 1; i < adj[u].size(); i++) {
                int v = adj[u][i];
                self(v, true);
            }
            if(adj[u].size()) {
                self(adj[u][0], false);
            }
            int col = bel[u - 1];
            cur -= 1LL * cnt[col] * (tot[col] - cnt[col]);
            cnt[bel[u - 1]]++;
            cur += 1LL * cnt[col] * (tot[col] - cnt[col]);
            for(int i = 1; i < adj[u].size(); i++) {
                int v = adj[u][i];
                add(v, 1);
            }
            ans += cur;
            if(del) {
                add(u, -1);
            }
        };
        dfs(1, false);
        return ans;
    }
};