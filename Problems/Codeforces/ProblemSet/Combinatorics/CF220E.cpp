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
    int n;
    ll k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> val{0};
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        val.push_back(a[i]);
    }

    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());
    vector<int> id(n + 1);
    for(int i = 1; i <= n; i++) {
        id[i] = lower_bound(val.begin() + 1, val.end(), a[i]) - val.begin();
    }
    int m = val.size();

    FenwickTree pre(m + 1), suf(m + 1);
    ll cnt = 0;
    for(int i = n; i >= 1; i--) {
        cnt += suf.query(id[i] - 1);
        suf.add(id[i], 1);
    }
    ll ans = 0;
    for(int l = 1, r = 2; r <= n; r++) {
        cnt -= pre.rangeQuery(id[r - 1] + 1, m);
        cnt -= suf.query(id[r - 1] - 1);
        suf.add(id[r - 1], -1);
        while(l < r) {
            ll w = pre.rangeQuery(id[l] + 1, m) + suf.query(id[l] - 1);
            if(cnt + w > k) {
                break;
            }
            cnt += w;
            pre.add(id[l], 1);
            l++;
        }
        ans += l - 1;
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
