#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc414/tasks/abc414_f
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
class SegmentTree {
private:
    int n;
    vector<ll> mn;
    vector<ll> tag;
public:
    SegmentTree(int x) : n(x), mn(x << 2, inf), tag(x << 2, inf) {}
    void push_up(int o) {
        mn[o] = min(mn[ls(o)], mn[rs(o)]);
    }
    void addtag(int o, ll d) {
        tag[o] = min(tag[o], d);
        mn[o] = min(mn[o], d);
    }
    void push_down(int o) {
        if(tag[o] != inf) {
            addtag(ls(o), tag[o]);
            addtag(rs(o), tag[o]);
            tag[o] = inf;
        }
    }
    void update(int L, int R, int o, int l, int r, ll d) {
        if(L <= l && r <= R) {
            addtag(o, d);
            return;
        }
        push_down(o);
        int mid = l + (r - l) / 2;
        if(L <= mid) update(L, R, ls(o), l, mid, d);
        if(R > mid) update(L, R, rs(o), mid + 1, r, d);
        push_up(o);
    }
    ll query_min(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mn[o];
        push_down(o);
        ll res = inf;
        int mid = l + (r - l) / 2;
        if(L <= mid) res = min(res, query_min(L, R, ls(o), l, mid));
        if(R > mid) res = min(res, query_min(L, R, rs(o), mid + 1, r));
        return res;
    }
};

struct info {
    int l, r;
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> id(n + 1), rid(n + 1);
    queue<int> q;
    q.push(1);
    int c = 0;
    vector<int> vis(n + 1);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        id[u] = ++c;
        rid[c] = u;
        vis[u] = true;
        for(int v : adj[u]) {
            if(!vis[v]) {
                q.push(v);
            }
        }
    }
    vector a(n + 1, vector<info>(k + 1, {inf,-inf}));
    vector<int> fa(n + 1);
    auto dfs = [&](auto &&self, int u, int f) -> void {
        fa[u] = f;
        a[u][0].l = a[u][0].r = id[u];
        for(int v : adj[u]) {
            if(v != f) {
                self(self, v, u);
                for(int i = 1; i <= k; i++) {
                    a[u][i].l = min(a[u][i].l, a[v][i - 1].l);
                    a[u][i].r = max(a[u][i].r, a[v][i - 1].r);
                }
            }
        }
    };
    dfs(dfs, 1, 0);
    SegmentTree dis(n + 1);
    dis.update(1, 1, 1, 1, n, 0);
    q.push(1);
    set<int> st;
    for(int i = 2; i <= n; i++) st.insert(i);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        c = 0;
        int cur = dis.query_min(id[u], id[u], 1, 1, n);
        int v = -1;
        while(u && c <= k) {
            auto [l, r] = a[u][k - c];
            int l2 = inf, r2 = -inf;
            if(v != -1 && c < k) {
                l2 = a[v][k - c - 1].l;
                r2 = a[v][k - c - 1].r;
            }
            c++;
            v = u;
            u = fa[u];
            if(l == inf) continue;
            if(l2 == inf) {
                dis.update(l, r, 1, 1, n, cur + 1);
                auto it = st.lower_bound(l);
                while(it != st.end() && (*it) <= r) {
                    q.push(rid[*it]);
                    it = st.erase(it);
                }
            } else {
                if(l < l2) {
                    dis.update(l, l2 - 1, 1, 1, n, cur + 1);
                    auto it = st.lower_bound(l);
                    while(it != st.end() && (*it) < l2) {
                        q.push(rid[*it]);
                        it = st.erase(it);
                    }
                }
                if(r > r2) {
                    dis.update(r2 + 1, r, 1, 1, n, cur + 1);
                    auto it = st.lower_bound(r2 + 1);
                    while(it != st.end() && (*it) <= r) {
                        q.push(rid[*it]);
                        it = st.erase(it);
                    }
                }
            }
        }
    }
    for(int i = 2; i <= n; i++) {
        int x = dis.query_min(id[i], id[i], 1, 1, n);
        if(x == inf) {
            cout << -1 << " ";
        } else {
            cout << x << " ";
        }
    }
    cout << "\n";
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
