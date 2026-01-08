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
        int l = 0, r = 0;
        ll v = 0;
        int sz = 0;
        unsigned int p = 0;
    };
    
    vector<Node> tr;
    int root = 0;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back({0, 0, 0, 0, 0});
    }

    int newNode(ll v) {
        tr.push_back({0, 0, v, 1, (unsigned int)rng()});
        return tr.size() - 1;
    }

    void pull(int u) {
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
    }

    void split(int u, ll v, int &x, int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        if(tr[u].v <= v) {
            x = u;
            split(tr[u].r, v, tr[u].r, y);
        } else {
            y = u;
            split(tr[u].l, v, x, tr[u].l);
        }
        pull(u);
    }

    int merge(int u, int v) {
        if(!u || !v) return u | v;
        if(tr[u].p > tr[v].p) {
            tr[u].r = merge(tr[u].r, v);
            pull(u);
            return u;
        } else {
            tr[v].l = merge(u, tr[v].l);
            pull(v);
            return v;
        }
    }

    void add(ll v) {
        int x, y;
        split(root, v, x, y);
        root = merge(merge(x, newNode(v)), y);
    }

    void remove(ll v) {
        int x, y, z;
        split(root, v, x, z);
        split(x, v - 1, x, y);
        if(y) {
            y = merge(tr[y].l, tr[y].r);
        }
        root = merge(merge(x, y), z);
    }

    int rank(ll v) {
        int x, y;
        split(root, v - 1, x, y);
        int res = tr[x].sz + 1;
        root = merge(x, y);
        return res;
    }

};

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    } 
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    FHQ tr(n);
    for(int i = 1; i <= n; i++) {
        tr.add(pre[i]);
    }
    int r = 1, mx = -1;
    ll offset = 0;
    for(int i = 1; i <= n; i++) {
        int cnt = n - tr.rank(offset + 1) + 1;
        if(cnt > mx) {
            mx = cnt;
            r = i;
        }
        tr.remove(pre[i]);
        offset += a[i];
        tr.add(pre[n] + offset);
    }
    cout << r - 1 << " " << mx << "\n";
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
