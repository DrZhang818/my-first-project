#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000007;
constexpr int MOD = 998244353;

void addM(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    vector<int> tr;
    int n;
    FenwickTree(int n) {
        this->n = n;
        tr.resize(n);
    }
    void reset(int n) {
        this->n = n;
        tr.assign(n, {});
    }
    void add(int o, int x) {
        for(; o < n; o += lowbit(o)) {
            addM(tr[o], x);
        }
    }
    int query(int o) {
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            addM(res, tr[o]);
        }
        return res;
    }
    int rangeQuery(int l, int r) {
        int res = query(r);
        addM(res, MOD - query(l - 1));
        return res;
    }
};
void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> val {0};
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        val.push_back(a[i]);
    }
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());
    int m = val.size();
    FenwickTree fen(m + 1);
    vector<int> pre(n + 1), suf(n + 1);
    for(int i = 1; i <= n; i++) {
        auto id = lower_bound(val.begin() + 1, val.end(), a[i]) - val.begin();
        pre[i] = fen.query(id - 1);
        addM(pre[i], 1);
        fen.add(id, pre[i]);
    }
    fen.reset(n + 1);
    for(int i = n; i >= 1; i--) {
        auto id = lower_bound(val.begin() + 1, val.end(), a[i]) - val.begin();
        suf[i] = fen.query(id - 1);
        addM(suf[i], 1);
        fen.add(id, suf[i]);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        addM(ans, 1LL * pre[i] * suf[i] % MOD);
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
