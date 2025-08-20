#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://www.luogu.com.cn/problem/P1361

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
    vector a(n + 1, vector<int>(m + 1));
    vector<ll> r(n + 1), c(m + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            r[i] += a[i][j];
            c[j] += a[i][j];
        }
    }
    int S = 0, T = n + m + 1;
    MaxFlow<ll> g(n + m + 2);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll cap = max(0LL, r[i]);
        g.addEdge(S, i, cap);
        ans += cap;
    }
    for(int j = 1; j <= m; j++) {
        ll cap = max(0LL, c[j]);
        g.addEdge(n + j, T, cap);
        ans += cap;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            g.addEdge(i, n + j, a[i][j] < 0 ? inf : a[i][j]);
        }
    }    
    cout << ans - g.flow(S, T) << "\n";
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
