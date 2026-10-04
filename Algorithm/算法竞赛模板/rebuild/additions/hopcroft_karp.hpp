#include <bits/stdc++.h>
using namespace std;
struct HopcroftKarp {
    int n, m, shortest;
    vector<vector<int>> g;
    vector<int> left, right, d, it;
    HopcroftKarp(int n_, int m_)
        : n(n_), m(m_), g(n + 1), left(n + 1), right(m + 1), d(n + 1), it(n + 1) {
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
    }
    bool bfs() {
        queue<int> q;
        fill(d.begin(), d.end(), -1);
        shortest = n + 1;
        for(int u = 1; u <= n; u++) {
            if(!left[u]) {
                d[u] = 0, q.push(u);
            }
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            if(d[u] >= shortest) {
                continue;
            }
            for(int v : g[u]) {
                int x = right[v];
                if(!x) {
                    shortest = d[u] + 1;
                } else if(d[x] < 0) {
                    d[x] = d[u] + 1, q.push(x);
                }
            }
        }
        return shortest <= n;
    }
    bool dfs(int s) {
        vector<int> a{s}, b;
        while(!a.empty()) {
            int u = a.back();
            bool go = false;
            while(it[u] < int(g[u].size())) {
                int v = g[u][it[u]++], x = right[v];
                if(!x && d[u] + 1 == shortest) {
                    b.push_back(v);
                    for(int i = 0; i < int(a.size()); i++) {
                        left[a[i]] = b[i], right[b[i]] = a[i];
                    }
                    return true;
                }
                if(x && d[x] == d[u] + 1) {
                    b.push_back(v);
                    a.push_back(x);
                    go = true;
                    break;
                }
            }
            if(!go) {
                d[u] = -1;
                a.pop_back();
                if(!b.empty()) {
                    b.pop_back();
                }
            }
        }
        return false;
    }
    int solve() {
        int ans = 0;
        for(int u = 1; u <= n; u++) {
            ans += left[u] != 0;
        }
        while(bfs()) {
            fill(it.begin(), it.end(), 0);
            for(int u = 1; u <= n; u++) {
                if(!left[u] && dfs(u)) {
                    ++ans;
                }
            }
        }
        return ans;
    }
    // Call after solve(). Return vertices in a minimum vertex cover.
    pair<vector<int>, vector<int>> minVertexCover() const {
        vector<bool> a(n + 1), b(m + 1);
        queue<int> q;
        for(int u = 1; u <= n; u++) {
            if(!left[u]) {
                a[u] = true, q.push(u);
            }
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int v : g[u]) {
                if(left[u] != v && !b[v]) {
                    b[v] = true;
                    if(right[v] && !a[right[v]]) {
                        a[right[v]] = true, q.push(right[v]);
                    }
                }
            }
        }
        vector<int> A, B;
        for(int u = 1; u <= n; u++) {
            if(!a[u]) {
                A.push_back(u);
            }
        }
        for(int v = 1; v <= m; v++) {
            if(b[v]) {
                B.push_back(v);
            }
        }
        return {A, B};
    }
};
