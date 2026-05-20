#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<int> tr;
    FenwickTree(int n) : n(n), tr(n) {}

    void add(int o, int d) {
        for(; o < n; o += lowbit(o)) {
            tr[o] += d;
        }
    }

    int query(int o) {
        int res = 0;
        for(; o; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
};

void solve() {
    int n, lo, hi;
    cin >> n >> lo >> hi;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<i64> x(n + 2), y(n + 2);
    i64 sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        x[i] = sum - 1LL * i * lo;
        y[i] = sum - 1LL * i * hi;
    }
    vector<int> p(n + 2);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(), 
        [&](int i, int j) {
            if(y[i] != y[j]) {
                return y[i] > y[j];
            }
            return x[i] < x[j];
        });

    auto val = x;
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());

    int sz = val.size();
    FenwickTree fen(sz);

    i64 ans = 0;

    for(int i = 1; i <= n + 1; i++) {
        auto idx = lower_bound(val.begin() + 1, val.end(), x[p[i]]) - val.begin();
        ans += fen.query(idx);
        fen.add(idx, 1);    
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
