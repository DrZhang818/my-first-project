#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
class SegmentTree {
private:
    struct node {
        char ch_L, ch_R;
        int len_L, len_R;
        int mx;
        int len;
    };
    vector<node> tr;
    string s;
public:
    SegmentTree(int x, string t) : tr(x << 2), s(t) {}
    node merge(node l, node r) {
        node res;
        res.len = l.len + r.len;
        res.ch_L = l.ch_L;
        res.ch_R = r.ch_R;
        res.len_L = l.len_L;
        if(l.len == l.len_L && r.ch_L == l.ch_L) res.len_L += r.len_L;
        res.len_R = r.len_R;
        if(r.len == r.len_R && l.ch_R == r.ch_R) res.len_R += l.len_R;
        res.mx = max(l.mx, r.mx);
        if(l.ch_R == r.ch_L) res.mx = max(res.mx, l.len_R + r.len_L);
        return res;
    }
    void build(int o, int l, int r) {
        if(l == r) {
            tr[o].ch_L = s[l];
            tr[o].ch_R = s[r];
            tr[o].len = tr[o].len_L = tr[o].len_R = tr[o].mx = 1;
            return;
        }
        int mid = l + r >> 1;
        build(ls(o), l, mid);
        build(rs(o), mid + 1, r);
        tr[o] = merge(tr[ls(o)], tr[rs(o)]);
    }
    void update(int i, int o, int l, int r, char x) {
        if(l == r) {
            tr[o] = node(x, x, 1, 1, 1, 1);
            return;
        }
        int mid = l + r >> 1;
        if(i <= mid) update(i, ls(o), l, mid, x);
        if(i > mid) update(i, rs(o), mid + 1, r, x);
        tr[o] = merge(tr[ls(o)], tr[rs(o)]);
    }
    node query(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return tr[o];
        int mid = l + r >> 1;
        if(R <= mid) return query(L, R, ls(o), l, mid);
        if(L > mid) return query(L, R, rs(o), mid + 1, r);
        return merge(query(L, mid, ls(o), l, mid), query(mid + 1, R, rs(o), mid + 1, r));
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    s = "#" + s;
    SegmentTree tr(n, s);
    tr.build(1, 1, n);
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i;
            char x;
            cin >> i >> x;
            tr.update(i, 1, 1, n, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r, 1, 1, n).mx << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
