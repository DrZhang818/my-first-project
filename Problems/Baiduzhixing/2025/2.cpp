#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

template<class T>
class MincostFlow {
private:
    struct _Edge {
        int to;
        T cap;
        T cost;
        _Edge(int to, T cap, T cost) : to(to), cap(cap), cost(cost) {}
    };
    int n;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<T> h, dis;
    vector<int> pre;
public:
    bool dijk(int s, int t) {
        dis.assign(n, numeric_limits<T>::max());
        pre.assign(n, -1);
        priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> que;
        dis[s] = 0;
        que.push({0, s});
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
                    que.push({dis[v], v});
                }
            }
        }
        return dis[t] != numeric_limits<T>::max();
    }
    MincostFlow(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        e.clear();
        g.assign(n, {});
    }
    void addEdge(int u, int v, T cap, T cost) {
        g[u].push_back(e.size());
        e.emplace_back(v, cap, cost);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -cost);
    }
    pair<T, T> flow(int s, int t) {
        T flow = 0;
        T cost = 0;
        h.assign(n, 0);
        while(dijk(s, t)) {
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
};

void solve() {
    int n, m, K, L;
    cin >> n >> m >> K >> L;

    int S = 0, T = 2 * K + 2 * L + 2 * m + 1;
    int N = K + L + 2 * m;
    vector<vector<int>> adj_a(n + 1), adj_b(n + 1);
    for(int i = 1; i <= K; i++) {
        int x;
        cin >> x;
        adj_a[x].push_back(i);
    }
    for(int i = 1; i <= L; i++) {
        int x;
        cin >> x;
        adj_b[x].push_back(K + i);
    }
    MincostFlow<int> graph(T + 1);
    for(int i = 1; i <= n; i++) {
        for(int x : adj_a[i]) {
            graph.addEdge(S, x, 1, 0);
            graph.addEdge(x, N + x, 1, 0);
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int y : adj_b[i]) {
            graph.addEdge(N + y, y, 1, 0);
            graph.addEdge(y, T, 1, 0);
        }
    }
    
    for(int i = 1; i <= n; i++) {
        for(int x : adj_a[i]) {
            for(int y : adj_b[i]) {
                graph.addEdge(N + x, N + y, 1, 0);
            }
        }
    }
    vector<vector<int>> nadj_a(n + 1);
    vector<vector<int>> nadj_b(n + 1);
    for(int i = 1; i <= m; i++) {
        int c, p, q;
        cin >> c >> p >> q;
        vector<int> ta(p + 1), tb(q + 1);
        for(int j = 1; j <= p; j++) {
            cin >> ta[j];
            nadj_a[ta[j]].push_back(K + L + i);
        }
        for(int j = 1; j <= q; j++) {
            cin >> tb[j];
            nadj_b[tb[j]].push_back(K + L + m + i);
        }
        graph.addEdge(K + L + i, K + L + m + i, c, 1);
        for(int j = 1; j <= p; j++) {
            for(int x : adj_a[ta[j]]) {
                graph.addEdge(N + x, K + L + i, 1, 0);
            }
        }
        for(int j = 1; j <= q; j++) {
            for(int y : adj_b[tb[j]]) {
                graph.addEdge(K + L + m + i, N + y, 1, 0);
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int y : nadj_b[i]) {
            for(int x : nadj_a[i]) {
                graph.addEdge(y, x, inf, 0);
            }
        }

    }
    auto [f, c] = graph.flow(S, T);
    if(f < K) {
        cout << -1 << "\n";
        return;
    }
    cout << c << "\n";
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