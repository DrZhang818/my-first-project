#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

template<class T>
class MaxFlow {
private:
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };
    int n;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<int> cur, h;
public:
    MaxFlow() {}
    MaxFlow(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }
    bool bfs(int s, int t) {
        h.assign(n, -1);
        queue<int> que;
        h[s] = 0;
        que.push(s);
        while(!que.empty()) {
            const int u = que.front();
            que.pop();
            for(int i : g[u]) {
                auto [v, c] = e[i];
                if(c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if(v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T f) {
        if(u == t) {
            return f;
        }
        auto r = f;
        for(int &i = cur[u]; i < int(g[u].size()); i++) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if(c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if(r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T flow(int s, int t) {
        T ans = 0;
        while(bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, numeric_limits<T>::max());
        }
        return ans;
    }
    vector<bool> minCut() {
        vector<bool> c(n);
        for(int i = 0; i < n; i++) {
            c[i] = (h[i] != -1);
        }
        return c;
    }
    struct Edge {
        int from;
        int to;
        T cap;
        T flow;
    };
    vector<Edge> edges() {
        vector<Edge> a;
        for(int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    int S = 0, T = 2 * n + 1;
    MaxFlow<int> g(T + 1);
    for(int i = 1; i <= n; i++) {
        g.addEdge(S, i, 1);
        g.addEdge(i + n, T, 1);
    }
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;  
        g.addEdge(u, v + n, 1);
    }
    auto f = g.flow(S, T);
    auto e = g.edges();
    vector<int> nxt(n + 1);
    vector<int> deg(n + 1);
    for(auto [from, to, _, flow] : e) {
        if(flow && 1 <= from && from <= n) {
            nxt[from] = to - n;
            deg[to - n]++;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(deg[i]) {
            continue;
        }
        int u = i;
        while(u) {
            cout << u << " ";
            u = nxt[u];
        }
        cout << "\n";
    }
    cout << n - f << "\n";
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
