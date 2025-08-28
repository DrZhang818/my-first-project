#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
class SegmentTree {
private:
    int n;
    vector<int> mn;
    vector<int> tag;
public:
    SegmentTree(int x) : n(x), mn(x << 2, inf), tag(x << 2, inf) {}
    void push_up(int o) {
        mn[o] = min(mn[ls(o)], mn[rs(o)]);
    }
    void addtag(int o, int l, int r, int d) {
        tag[o] = min(tag[o], d);
        mn[o] = min(mn[o], d);
    }
    void push_down(int o, int l, int r) {
        if(tag[o] != inf) {
            int mid = l + (r - l) / 2;
            addtag(ls(o), l, mid, tag[o]);
            addtag(rs(o), mid + 1, r, tag[o]);
            tag[o] = inf;
        }
    }
    void update(int L, int R, int o, int l, int r, int d) {
        if(L <= l && r <= R) {
            addtag(o, l, r, d);
            return;
        }
        push_down(o, l, r);
        int mid = l + (r - l) / 2;
        if(L <= mid) update(L, R, ls(o), l, mid, d);
        if(R > mid) update(L, R, rs(o), mid + 1, r, d);
        push_up(o);
    }
    int query_min(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mn[o];
        push_down(o, l, r);
        int res = inf;
        int mid = l + (r - l) / 2;
        if(L <= mid) res = min(res, query_min(L, R, ls(o), l, mid));
        if(R > mid) res = min(res, query_min(L, R, rs(o), mid + 1, r));
        return res;
    }
};

struct info {
    int l, r, w;
    friend bool operator < (const info &a, const info &b) {
        return a.l < b.l;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    SegmentTree tr(n);
    vector<info> a(q + 1);
    for(int i = 1; i <= q; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        a[i] = {l, r, c};
    }

    sort(a.begin() + 1, a.end());

    int L = a[1].l, R = a[1].r;
    tr.update(a[1].l, a[1].r, 1, 1, n, a[1].w);

    ll sum = 0;
    for(int i = 2; i <= q; i++) {
        if(a[i].l > R) {
            cout << -1 << "\n";
            return;
        }
        int c = tr.query_min(a[i].l, a[i].r, 1, 1, n);
        sum += max(c, a[i].w);
        tr.update(a[i].l, a[i].r, 1, 1, n, a[i].w);
        R = max(R, a[i].r);
    }

    bool ok = true;
    for(int i = 1; i <= n; i++) {
        int c = tr.query_min(i, i, 1, 1, n);
        if(c == inf) {
            ok = false;
            break;
        }
        sum += c;
    }
    if(!ok) {
        cout << -1 << "\n";
        return;
    }
    cout << sum << "\n";
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
