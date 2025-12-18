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
        int l = 0, r = 0, v = 0, sz = 0;
        bool rev = false;   
        unsigned int p = 0;
    };
    
    vector<Node> tr;
    int root = 0;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back({0, 0, 0, 0, false, 0});
    }

    int newNode(int v) {
        tr.push_back({0, 0, v, 1, false, (unsigned int)rng()});
        return tr.size() - 1;
    }

    void pull(int u) {
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
    }

    void push(int u) {
        if(u && tr[u].rev) {
            swap(tr[u].l, tr[u].r);
            if(tr[u].l) tr[tr[u].l].rev ^= 1;
            if(tr[u].r) tr[tr[u].r].rev ^= 1;
            tr[u].rev = false;
        }
    }

    void split(int u, int k, int &x, int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        push(u);
        if(tr[tr[u].l].sz + 1 <= k) {
            x = u;
            split(tr[u].r, k - tr[tr[u].l].sz - 1, tr[u].r, y);
        } else {
            y = u;
            split(tr[u].l, k, x, tr[u].l);
        }
        pull(u);
    }

    int merge(int u, int v) {
        if(!u || !v) return u | v;
        if(tr[u].p > tr[v].p) {
            push(u);
            tr[u].r = merge(tr[u].r, v);
            pull(u);
            return u;
        } else {
            push(v);
            tr[v].l = merge(u, tr[v].l);
            pull(v);
            return v;
        }
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

    void reverse(int l, int r) {
        int x, y, z;
        split(root, r, x, z);
        split(x, l - 1, x, y);
        if(y) {
            tr[y].rev ^= 1;
        }
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
    int n, q, m;
    cin >> n >> q >> m;
    FHQ tr(n);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tr.root = tr.merge(tr.root, tr.newNode(x));
    }
    while(q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if(op == 1) {
            tr.shift(l, r);
        } else {
            tr.reverse(l, r);
        }
    }
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        cout << tr.query(x) << " \n"[i == m];
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
