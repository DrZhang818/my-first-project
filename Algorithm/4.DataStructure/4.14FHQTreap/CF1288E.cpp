#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct FHQ {
    struct Node {
        int l = 0, r = 0, v = 0, sz = 0, fa = 0;
        bool rev = false;   
        unsigned int p = 0;
    };
    
    vector<Node> tr;
    int root = 0;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back({0, 0, 0, 0, 0, false, 0});
    }

    int newNode(int v) {
        tr.push_back({0, 0, v, 1, 0, false, (unsigned int)rng()});
        return tr.size() - 1;
    }

    void pull(int u) {
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
    }

    void split(int u, int k, int &x, int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        if(tr[tr[u].l].sz + 1 <= k) {
            x = u;
            split(tr[u].r, k - tr[tr[u].l].sz - 1, tr[u].r, y);
            if(tr[u].r) tr[tr[u].r].fa = u;
        } else {
            y = u;
            split(tr[u].l, k, x, tr[u].l);
            if(tr[u].l) tr[tr[u].l].fa = u;
        }
        pull(u);
    }

    int merge(int u, int v) {
        if(!u || !v) return u | v;
        if(tr[u].p > tr[v].p) {
            tr[u].r = merge(tr[u].r, v);
            if(tr[u].r) tr[tr[u].r].fa = u;
            pull(u);
            return u;
        } else {
            tr[v].l = merge(u, tr[v].l);
            if(tr[v].l) tr[tr[v].l].fa = v;
            pull(v);
            return v;
        }
    }

    int rank(int u) {
        int res = tr[tr[u].l].sz + 1;
        while(u != root) {
            int fa = tr[u].fa;
            if(tr[fa].r == u) {
                res += tr[tr[fa].l].sz + 1;
            }
            u = fa;
        }
        return res;
    }

    void shift(int l, int r) {
        int x, y, z;
        split(root, r, x, z);
        split(x, l - 1, x, y);
        int a, b;
        split(y, r - l, a, b);
        y = merge(b, a);
        root = merge(merge(x, y), z);
    }

    int query(int k) {
        int x, y, z;
        split(root, k, x, z);
        split(x, k - 1, x, y);
        int res = tr[y].v;
        root = merge(merge(x, y), z);
        return res;
    }
};

void solve() {  
    int n, q;
    cin >> n >> q;
    FHQ tr(n);
    vector<int> mn(n + 1), mx(n + 1);
    for(int i = 1; i <= n; i++) {
        mn[i] = mx[i] = i;
        tr.root = tr.merge(tr.root, tr.newNode(i));
    }
    while(q--) {
        int x;
        cin >> x;
        int k = tr.rank(x);
        mx[x] = max(mx[x], k);
        tr.shift(1, k);
        mn[x] = 1;
    }
    for(int i = 1; i <= n; i++) {
        int k = tr.rank(i);
        mx[i] = max(mx[i], k);
        cout << mn[i] << " " << mx[i] << "\n";
    }
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
