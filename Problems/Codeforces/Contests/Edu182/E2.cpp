#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

inline int ls(int o) { return o << 1; };
inline int rs(int o) { return o << 1 | 1; }
class SegmentTree {
    int n;
    vector<int> sum, tag;
    void push_up(int o) {
        sum[o] = ((ll)sum[ls(o)] + sum[rs(o)]) % MOD;
    }
    void add_tag(int o, int x) {
        sum[o] = 1LL * sum[o] * x % MOD;
        tag[o] = 1LL * tag[o] * x % MOD;
    }
    void push_down(int o) {
        if(tag[o] != 1) {
            add_tag(ls(o), tag[o]);
            add_tag(rs(o), tag[o]);
            tag[o] = 1;
        }
    }
    void mul(int L, int R, int o, int l, int r, int x) {
        if(L <= l && r <= R) {
            add_tag(o, x);
            return;
        }
        push_down(o);
        int mid = l + r >> 1;
        if(L <= mid) mul(L, R, ls(o), l, mid, x);
        if(R > mid) mul(L, R, rs(o), mid + 1, r, x);
        push_up(o);
    }
    void modify(int p, int o, int l, int r, int x) {
        if(l == r) {
            sum[o] = x;
            tag[o] = 1;
            return;
        }
        push_down(o);
        int mid = l + r >> 1;
        if(p <= mid) modify(p, ls(o), l, mid, x);
        else modify(p, rs(o), mid + 1, r, x);
        push_up(o);
    }
    int query(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) {
            return sum[o];
        }
        push_down(o);
        int mid = l + r >> 1;
        int res = 0;
        if(L <= mid) add(res, query(L, R, ls(o), l, mid));
        if(R > mid) add(res, query(L, R, rs(o), mid + 1, r));
        return res;
    }
public:
    SegmentTree(int x) : n(x), sum(x << 2), tag(x << 2, 1) {}
    void modify(int p, int x) {
        modify(p, 1, 1, n, x);
    }
    void mul(int l, int r, int x) {
        mul(l, r, 1, 1, n, x);
    }
    int query(int l, int r) {
        return query(l, r, 1, 1, n);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int mx = ranges::max(a);
    auto work = [&]() {
        vector<int> pre{0};
        for(int i = 1; i <= n; i++) {
            if(a[i] > pre.back()) {
                pre.push_back(a[i]);
            }
        }
        int m = pre.size() - 1;
        vector<int> f(n + 1);
        SegmentTree tr(m + 1);
        for(int i = 1; i <= n; i++) {
            auto pos = lower_bound(pre.begin() + 1, pre.end(), a[i]) - pre.begin();
            tr.mul(pos, m, 2);
            if(pre[pos] == a[i]) {
                if(pos == 1) {
                    f[i] = 1;
                    tr.modify(1, (tr.query(1, 1) + 1) % MOD);
                } else {
                    f[i] = tr.query(pos - 1, pos - 1);
                    tr.modify(pos, tr.query(pos - 1, pos));
                }
            }
        }
        return f;
    };
    auto L = work();
    reverse(a.begin() + 1, a.end());
    auto R = work();
    reverse(a.begin() + 1, a.end());
    reverse(R.begin() + 1, R.end());
    int ans = 0, sum = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == mx) {
            add(ans, 1LL * L[i] * R[i] % MOD);
            add(ans, 1LL * sum * R[i] % MOD);
        }
        sum = 2LL * sum % MOD;
        if(a[i] == mx) {
            add(sum, L[i]);
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
