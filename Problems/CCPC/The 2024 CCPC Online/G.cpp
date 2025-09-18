#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

template<class T> 
struct MinCostFlow {
    struct _Edge {
        int to;
        T cap;
        T cost;
        _Edge(int to_, T cap_, T cost_) : to(to_), cap(cap_), cost(cost_) {}
    };
    int n;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<T> h, dis;
    vector<int> pre;
    bool dijkstra(int s, int t) {
        dis.assign(n, numeric_limits<T>::max());
        pre.assign(n, -1);
        priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> que;
        dis[s] = 0;
        que.emplace(0, s);
        while(!que.empty()) {
            T d = que.top().first;
            int u = que.top().second;
            que.pop();
            if(dis[u] != d) {
                continue;
            }
            for(int i : g[u]) {
                int v = e[i].to;
                T cap = e[i].cap;
                T cost = e[i].cost;
                if(cap > 0 && dis[v] > d + h[u] - h[v] + cost) {
                    dis[v] = d + h[u] - h[v] + cost;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != numeric_limits<T>::max();
    }
    MinCostFlow() {}
    MinCostFlow(int n_) { 
        init(n_);
    }
    void init(int n_) {
        n = n_;
        e.clear();
        g.assign(n, {});
    }
    void addEdge(int u, int v, T cap, T cost) {
        g[u].emplace_back(e.size());
        e.emplace_back(v, cap, cost);
        g[v].emplace_back(e.size());
        e.emplace_back(u, 0, -cost);
    }
    pair<T, T> flow(int s, int t) {
        T flow = 0;
        T cost = 0;
        h.assign(n, 0);
        while(dijkstra(s, t)) {
            for(int i = 0; i < n; i++) {
                h[i] += dis[i];
            }
            T aug = numeric_limits<int>::max();
            for(int i = t; i != s; i = e[pre[i] ^ 1].to) {
                aug = min(aug, e[pre[i]].cap);
            }
            for(int i = t; i != s; i = e[pre[i] ^ 1].to) {
                e[pre[i]].cap -= aug;
                e[pre[i] ^ 1].cap += aug;
            }
            flow += aug;
            cost += aug * h[t];
        }
        return make_pair(flow, cost);
    }
    struct Edge {
        int from;
        int to;
        T cap;
        T cost;
        T flow;
    };
    vector<Edge> edges() {
        vector<Edge> a;
        for(int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.cost = e[i].cost;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};

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
    
    int S = 0, T = 2 * n + m + 1;
    MinCostFlow<ll> g(T + 1);

    vector<int> a(n + 1), V(n + 1); 
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> V[i];
        if(i == 1) {
            g.addEdge(S, i, a[i] - V[i], 0);
        } else {
            g.addEdge(S, i, a[i] - V[i], 1);
        }
        g.addEdge(i, i + n, inf, 0);
    }
    ll sum = 0;
    vector<tuple<int,int,int>> b(m + 1);
    for(int i = 1; i <= m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        b[i] = {x, y, w};
        sum += w;
        if(x == y) {
            g.addEdge(x + n, i + 2 * n, inf, 0);
        } else {
            g.addEdge(x + n, i + 2 * n, inf, 0);
            g.addEdge(y + n, i + 2 * n, inf, 0);
        }
        g.addEdge(i + 2 * n, T, w, 0);
    }
    auto [f, c] = g.flow(S, T);
    if(f != sum) {
        cout << "NO\n";
        return;
    }
    auto e = g.edges();
    ll mx = 0;
    for(auto &[u, v, _1, _2, flow] : e) {
        if(v == 1) {
            mx = flow;
        }
    }

    mx += V[1];
    for(int i = 2; i <= n; i++) {
        if(V[i] >= mx) {
            cout << "NO\n";
            return;
        }
    }

    MaxFlow<ll> g2(T + 1);
    for(int i = 1; i <= n; i++) {
        if(i != 1) {
            g2.addEdge(S, i, min((ll)a[i] - V[i], mx - V[i] - 1));
        } else {
            g2.addEdge(S, i, a[i] - V[i]);
        }
        g2.addEdge(i, i + n, inf);
    }
    for(int i = 1; i <= m; i++) {
        auto [x, y, w] = b[i];
        if(x == y) {
            g2.addEdge(x + n, i + 2 * n, inf);
        } else {
            g2.addEdge(x + n, i + 2 * n, inf);
            g2.addEdge(y + n, i + 2 * n, inf);
        }
        g2.addEdge(i + 2 * n, T, w);
    }
    auto f2 = g2.flow(S, T);
    if(f2 != sum) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
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
