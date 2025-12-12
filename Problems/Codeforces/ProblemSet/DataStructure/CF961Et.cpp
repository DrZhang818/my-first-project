#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct PersistentSegTree {
    struct Info {
        int cnt;
    };
    struct Node {
        int lo, ro;
        Info info;
    };
    vector<Node> tr;
    PersistentSegTree(int n) {
        tr.reserve(n * 20);
    }
    Info merge(const Info& l, const Info& r) {
        return {l.cnt + r.cnt};
    }
    void pull(int o) {
        tr[o].info = merge(tr[tr[o].lo].info, tr[tr[o].ro].info);
    }
    int build(int l, int r) {
        tr.push_back({0, 0, {0}});
        int o = tr.size() - 1;
        if(l == r) return o;
        int mid = l + r >> 1;
        tr[o].lo = build(l, mid);
        tr[o].ro = build(mid + 1, r);
        pull(o);
        return o;
    }
    int update(int prev, int l, int r, int i) {
        tr.push_back(tr[prev]);
        int o = tr.size() - 1;
        if(l == r) {
            tr[o].info.cnt++;
            return o;
        }
        int mid = l + r >> 1;
        if(i <= mid) {
            tr[o].lo = update(tr[prev].lo, l, mid, i);
        } else {
            tr[o].ro = update(tr[prev].ro, mid + 1, r, i);
        }
        pull(o);
        return o;
    }
    Info query(int o, int l, int r, int ql, int qr) {
        if(ql <= l && r <= qr) return tr[o].info;
        int mid = l + r >> 1;
        if(qr <= mid) return query(tr[o].lo, l, mid, ql, qr);
        if(mid < ql) return query(tr[o].ro, mid + 1, r, ql, qr);
        return merge(query(tr[o].lo, l, mid, ql, qr),
                     query(tr[o].ro, mid + 1, r, ql, qr));
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> val(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        val[i] = a[i];
    }

    PersistentSegTree seg(n);
    vector<int> roots;
    roots.push_back(seg.build(1, n));

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
    cerr << i << "\n";
        int r = min(a[i], i - 1);
        ans += r - seg.query(roots[r], 1, n, 1, i - 1).cnt;
        roots.push_back(seg.update(roots.back(), 1, n, min(a[i], n)));
        cerr << "!\n";
    }
    cout << ans << "\n";
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
