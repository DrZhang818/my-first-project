#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

struct FenwickTree {
    int n;
    vector<int> tr;
    FenwickTree(int n) : n(n), tr(n) {}
    void add(int o, int x) { 
        for(; o < n; o += o & -o) tr[o] += x;
    }
    int query(int o) {
        int res = 0;
        for(; o; o -= o & -o) res += tr[o];
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

    i64 ans = 0;

    auto work = [&](int l, int r) {
        FenwickTree fen(n + 1);
        i64 sum = 0;
        vector<i64> val {0};
        for(int i = l; i <= r; i++) {
            sum += (i - l) % 2 == 0 ? a[i] : -a[i];
            val.push_back(sum);
        }
        sort(val.begin(), val.end());
        val.erase(unique(val.begin(), val.end()), val.end());

        int p0 = lower_bound(val.begin(), val.end(), 0) - val.begin() + 1;
        fen.add(p0, 1);
        
        sum = 0;
        for(int i = l; i <= r; i++) {
            sum += (i - l) % 2 == 0 ? a[i] : -a[i];
            if((i - l) & 1) {
                int p = lower_bound(val.begin(), val.end(), sum) - val.begin() + 1;
                fen.add(p, 1);
            } else {
                int p = lower_bound(val.begin(), val.end(), sum) - val.begin() + 1;
                ans += fen.query(p - 1);
            }
        }
    };

    work(1, n);
    work(2, n);

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}