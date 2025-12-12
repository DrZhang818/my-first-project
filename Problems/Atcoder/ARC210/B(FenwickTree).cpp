#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<ll> tr;
    FenwickTree(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        tr.assign(n, {});
    }
    void add(int o, ll x) {
        for(; o < n; o += lowbit(o)) {
            tr[o] += x;
        }
    }
    ll query(int o) {
        ll res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
    ll rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
    int select(ll k) {
        int x = 0;
        ll cur = 0;
        for(int i = 1 << __lg(n); i; i >>= 1) {
            if(x + i < n && cur + tr[x + i] < k) {
                x += i;
                cur += tr[x];
            }
        }
        return x + 1;
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1), b(m + 1);
    vector<int> val(n + m + q + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        val[i] = a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
        val[n + i] = b[i];
    }
    vector<array<int,3>> Q(q);
    for(int i = 0; i < q; i++) {
        cin >> Q[i][0] >> Q[i][1] >> Q[i][2];
        val[n + m + i + 1] = Q[i][2];
    }

    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());
    int sz = val.size();

    FenwickTree fen_cnt(sz + 1), fen_sum(sz + 1);
    auto add = [&](int x, int d1, int d2) -> void {
        auto id = lower_bound(val.begin() + 1, val.end(), x) - val.begin();
        fen_cnt.add(id, d1);
        fen_sum.add(id, d2);
    };

    for(int i = 1; i <= n + m; i++) {
        int x = i <= n ? a[i] : b[i - n];
        add(x, 1, x);
    }

    for(auto [op, i, upd] : Q) {
        int pre = op == 1 ? a[i] : b[i];
        add(pre, -1, -pre);

        op == 1 ? (a[i] = upd) : (b[i] = upd);
        add(upd, 1, upd);
        
        ll ans = 0;
        int id = fen_cnt.select(n / 2);
        int x = val[id];
        ll sum1 = fen_sum.query(id - 1) + 1LL * (n / 2 - fen_cnt.query(id - 1)) * x;
        ans += sum1;

        id = fen_cnt.select(m + n / 2 + 1);
        x = val[id];
        ll sum2 = fen_sum.rangeQuery(id + 1, sz) + 1LL * (n / 2 - fen_cnt.rangeQuery(id + 1, sz)) * x;
        ans += sum2;        

        cout << ans << "\n";
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
