#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

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

void solve() {
    int n, m;
    cin >> n >> m;
    MinCostFlow<int> g(n + 3);
    int S = 0, T = n + 2;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }  
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        int x = a[i] - a[i - 1];
        if(x > 0) {
            g.addEdge(S, i, x, 0);
        } else if(x < 0) {
            g.addEdge(i, T, -x, 0);
            tot -= x;
        }
    }
    g.addEdge(S, n + 1, inf, 0);

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(v + 1, u, inf, 1);
    }

    auto [flow, cost] = g.flow(S, T);
    if(flow != tot) {
        cout << -1 << "\n";
        return;
    }
    cout << cost << "\n";
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
