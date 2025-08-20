#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://www.luogu.com.cn/problem/P2762

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
    int m, n;
    cin >> m >> n;
    cin.ignore();
    MaxFlow<ll> g(m + n + 2);
    ll ans = 0;
    for(int i = 1; i <= m; i++) {
        string s;
        getline(cin, s);
        istringstream ss(s);
        int p, x;
        ss >> p;
        ans += p;
        g.addEdge(0, i, p);
        while(ss >> x) {
            g.addEdge(i, x + m, inf);
        }
    }
    for(int i = m + 1; i <= m + n; i++) {
        int c;
        cin >> c;
        g.addEdge(i, m + n + 1, c);
    }
    ans -= g.flow(0, m + n + 1);
    auto a = g.minCut();
    for(int i = 1; i <= m; i++) {
        if(a[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
    for(int i = m + 1; i <= m + n; i++) {
        if(a[i]) {
            cout << i - m << " ";
        }
    }
    cout << "\n";
    cout << ans << "\n";
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
