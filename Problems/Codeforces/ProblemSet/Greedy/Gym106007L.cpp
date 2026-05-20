#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    int _or = 0, _and = (1 << 30) - 1;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        _or |= a[i];
        _and &= a[i];
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] != _or) {
            ans++;
            i += m - 1;
        }
    }

    int msk = _or ^ _and;

    int q;
    cin >> q;
    while(q--) {
        int x;
        cin >> x;
        if((x & msk) != msk) {
            cout << -1 << "\n";
        } else if((x & _or) == x || ans == 0) {
            cout << ans << "\n";
        } else {
            cout << (n + m - 1) / m << "\n";
        }
    }
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