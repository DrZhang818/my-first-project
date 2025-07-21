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
    int n;
    vector<int> mx, mn;
    vector<int> tag;
public:
    SegmentTree(int x) : n(x), mx(x << 2), mn(x << 2), tag(x << 2) {}
    void push_up(int o) {
        mx[o] = max(mx[ls(o)], mx[rs(o)]);
        mn[o] = min(mn[ls(o)], mn[rs(o)]);
    }
    void addtag(int o, int l, int r, int d) {
        tag[o] += d;
        mx[o] += d;
        mn[o] += d;
    }
    void push_down(int o, int l, int r) {
        if(tag[o]) {
            int mid = l + (r - l) / 2;
            addtag(ls(o), l, mid, tag[o]);
            addtag(rs(o), mid + 1, r, tag[o]);
            tag[o] = 0;
        }
    }
    void add(int L, int R, int o, int l, int r, int d) {
        if(L <= l && r <= R) {
            addtag(o, l, r, d);
            return;
        }
        push_down(o, l, r);
        int mid = l + (r - l) / 2;
        if(L <= mid) add(L, R, ls(o), l, mid, d);
        if(R > mid) add(L, R, rs(o), mid + 1, r, d);
        push_up(o);
    }
    int query_max(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mx[o];
        push_down(o, l, r);
        int res = -inf;
        int mid = l + (r - l) / 2;
        if(L <= mid) res = max(res, query_max(L, R, ls(o), l, mid));
        if(R > mid) res = max(res, query_max(L, R, rs(o), mid + 1, r));
        return res;
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<int>> pos(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    int ans = -inf, c = 0;
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j : pos[i]) {
            b[++c] = j;
        }
    }
    SegmentTree tr(n + 2);
    for(int i = 2; i <= n + 1; i++) tr.add(i, i, 1, 1, n + 1, i - 1);
    auto ck = [&](int j) -> bool {
        return tr.query_max(j + 1, n + 1, 1, 1, n + 1) >= tr.query_min(1, j, 1, 1, n + 1);
    };
    for(int i = 1, j = 1; i <= n; i++) {
        while(j <= n && !ck(b[j])) j++;
        if(j > n) break;
        ans = max(ans, i - a[b[j]]);
        for(int p : pos[i]) {
            tr.add(p + 1, n + 1, 1, 1, n + 1, -2);
        }
    }
    cout << ans << "\n";
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
