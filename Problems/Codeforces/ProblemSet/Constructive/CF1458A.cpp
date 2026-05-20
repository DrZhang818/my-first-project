#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> a(n);
    i64 mx = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    i64 g = 0;
    for(int i = 0; i < n; i++) {
        g = gcd(g, mx - a[i]);
    }
    for(int i = 0; i < m; i++) {
        i64 x;
        cin >> x;
        cout << gcd(mx + x, g) << " \n"[i == m - 1];
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
