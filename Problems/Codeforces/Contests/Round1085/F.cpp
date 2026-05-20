#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

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
    vector<int> r(n * m), c(n * m);
    for(int i = 0; i < n * m; i++) {
        cin >> r[i];
        r[i]--;
    }    
    for(int i = 0; i < n * m; i++) {
        cin >> c[i];
        c[i]--;
    }

    vector<int> pos(n * m);
    for(int i = 0; i < n * m; i++) {
        pos[c[i] * n + r[i]] = i;
    }

    vector<bool> valid(n * m);
    for(int j = 0; j < m; j++) {
        int left = inf;
        for(int i = n - 1; i >= 0; i--) {
            int p = pos[j * n + i];
            if(p < left) {
                valid[j * n + i] = true;
                left = p;
            }
        }
    }

    vector<int> P;
    vector<int> P_id(n, -1);
    for(int i = 0; i < n; i++) {
        bool ok = true;
        for(int j = 0; j < m; j++) {
            if(!valid[j * n + i]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            P_id[i] = P.size();
            P.push_back(i);
        }
    }

    if(P.empty()) {
        cout << n - 1 << "\n";
        return;
    }

    int cnt = 0;
    vector<int> seg_id(n * m, -1);
    for(int j = 0; j < m; j++) {
        for(int l = 0, r = 0; l < n; l = r) {
            while(r < n && valid[j * n + r] == valid[j * n + l]) {
                r++;
            }
            if(!valid[j * n + l]) {
                continue;
            }
            for(int k = l; k < r; k++) {
                seg_id[j * n + k] = cnt;
            }
            cnt++;
        }
    }

    int S = 0, T = P.size() + cnt + 1;
    MaxFlow<int> g(T + 1);
    for(int i = 0; i < P.size(); i++) {
        g.addEdge(S, i + 1, 1);
    }
    for(int i = 0; i < cnt; i++) {
        g.addEdge(P.size() + i + 1, T, 1);
    }
    for(int i : P) {
        for(int j = 0; j < m; j++) {
            g.addEdge(P_id[i] + 1, seg_id[j * n + i] + P.size() + 1, 1);
        }
    }

    auto flow = g.flow(S, T);
    cout << n - P.size() + flow - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
