#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct FenwickTree {
    int n;
    vector<int> tr;
    FenwickTree(int n) : n(n), tr(n, inf) {}
    void add(int o, int x) {
        for(; o < n; o += o & -o) {
            tr[o] = min(tr[o], x);
        }
    }
    int query(int o) {
        int res = inf;
        for(; o > 0; o -= o & -o) {
            res = min(res, tr[o]);
        }
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

    int ans = 0;
    {
        FenwickTree fen(n + 1);
        for(int i = 1; i <= n; i++) {
            int mn = fen.query(a[i]);
            ans = max(ans, a[i] - i - mn);
            fen.add(a[i], a[i] - i);
        }
    }
    {
        FenwickTree fen(n + 1);
        for(int i = n; i >= 1; i--) {
            int mn = fen.query(a[i]);
            ans = max(ans, a[i] + i - mn);
            fen.add(a[i], a[i] + i);
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
