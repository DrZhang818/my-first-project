#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n, q, root, MOD, idx = 0;
vector<int> fa, son, sz, dep, top, id;
vector<ll> w, nw, tr, tag;
vector<vector<int>> adj;
void init() {
    fa.resize(n + 1);
    son.resize(n + 1);
    sz.resize(n + 1);
    dep.resize(n + 1);
    top.resize(n + 1);
    id.resize(n + 1);
    w.resize(n + 1);
    nw.resize(n + 1);
    adj.resize(n + 1);
    tr.resize(n << 2);
    tag.resize(n << 2);
}
void dfs1(int u, int f) {
    fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1;
    for(int v : adj[u]) {
        if(v == f) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) {
            son[u] = v;
        }
    }
}
void dfs2(int u, int t) {
    top[u] = t, id[u] = ++idx, nw[idx] = w[u];
    if(!son[u]) return;
    dfs2(son[u], t);
    for(int v : adj[u]) {
        if(v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o) {
    tr[o] = (tr[ls(o)] + tr[rs(o)]) % MOD;
}
void build(int o, int l, int r) {
    if(l == r) {
        tr[o] = nw[l] % MOD;
        return;
    }
    int mid = l + r >> 1;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
    push_up(o);
}
void add_tag(int o, int l, int r, ll d) {
    tag[o] = (tag[o] + d) % MOD;
    tr[o] = (tr[o] + (ll)d * (r - l + 1) % MOD) % MOD;
}
void push_down(int o, int l, int r) {
    if(tag[o]) {
        int mid = l + r >> 1;
        add_tag(ls(o), l, mid, tag[o]);
        add_tag(rs(o), mid + 1, r, tag[o]);
        tag[o] = 0;
    }
}
void add(int L, int R, int o, int l, int r, ll d) {
    if(L <= l && r <= R) {
        add_tag(o, l, r, d);
        return;
    }
    push_down(o, l, r);
    int mid = l + r >> 1;
    if(L <= mid) add(L, R, ls(o), l, mid, d);
    if(R > mid) add(L, R, rs(o), mid + 1, r, d);
    push_up(o);
}
ll sum(int L, int R, int o, int l, int r) {
    if(L <= l && r <= R) return tr[o];
    push_down(o, l, r);
    ll res = 0;
    int mid = l + r >> 1;
    if(L <= mid) res = (res + sum(L, R, ls(o), l, mid)) % MOD;
    if(R > mid) res = (res + sum(L, R, rs(o), mid + 1, r)) % MOD;
    return res;
}
void op1(int u, int v, ll d) {
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        add(id[top[u]], id[u], 1, 1, n, d);
        u = fa[top[u]];
    }
    if(id[u] > id[v]) swap(u, v);
    add(id[u], id[v], 1, 1, n, d);
}
ll op2(int u, int v) {
    ll res = 0;
    while(top[u] != top[v]) {
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        res = (res + sum(id[top[u]], id[u], 1, 1, n)) % MOD;
        u = fa[top[u]];
    }
    if(id[u] > id[v]) swap(u, v);
    res = (res + sum(id[u], id[v], 1, 1, n)) % MOD;
    return res;
}
void op3(int u, ll d) {
    add(id[u], id[u] + sz[u] - 1, 1, 1, n, d);
}
ll op4(int u) {
    return sum(id[u], id[u] + sz[u] - 1, 1, 1, n);
}
void solve() { 
    cin >> n >> q >> root >> MOD;
    init();
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(root, 0);
    dfs2(root, root);
    build(1, 1, n);
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int x, y;
            ll d;
            cin >> x >> y >> d;
            op1(x, y, d);
        } else if(flag == 2) {
            int x, y;
            cin >> x >> y;
            cout << op2(x, y) << "\n";
        } else if(flag == 3) {
            int x;
            ll d;
            cin >> x >> d;
            op3(x, d);
        } else {
            int x;
            cin >> x;
            cout << op4(x) << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
