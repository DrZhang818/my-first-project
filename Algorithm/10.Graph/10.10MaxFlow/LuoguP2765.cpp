#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 1567;

int num[N + 1];

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
        cur.assign(n, 0);
        h.assign(n, 0);
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
    int n;
    cin >> n;

    MaxFlow<int> g;
    int f;
    auto ck = [&](int x) -> bool {
        int S = 0, T = 2 * x + 1;
        g.init(T + 1);
        for(int i = 1; i <= x; i++) {
            g.addEdge(S, i, 1);
            g.addEdge(i + x, T, 1);
            auto j = upper_bound(num + 1, num + N + 1, 2 * i) - num;
            for(j; j <= N; j++) {
                int y = num[j];
                if(y - i > x) {
                    break;
                }
                g.addEdge(i, y - i + x, 1);
            }
        }
        f = g.flow(S, T);
        return x - f <= n;
    };

    int l = 0, r = N + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";

    ck(l);
    auto e = g.edges();
    vector<int> nxt(l + 1), deg(l + 1);
    for(auto &[from, to, _, flow] : e) {
        if(flow && 1 <= from && from <= l) {
            nxt[from] = to - l;
            deg[to - l]++;
        }
    }
    for(int i = 1; i <= l; i++) {
        if(!deg[i]) {
            int u = i;
            while(u) {
                cout << u << " \n"[nxt[u] == 0];
                u = nxt[u];
            }
        }
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= N; i++) {
        num[i] = i * i;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
