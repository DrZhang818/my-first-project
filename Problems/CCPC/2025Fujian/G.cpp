#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<i64> d(n + 1);
    for(int i = 1; i <= n; i++) {
        d[i] = max(0, a[i] - a[i - 1]);
        d[i] += d[i - 1];
    }

    int k;
    cin >> k;
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << k + d[r] - d[l] << "\n";
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}