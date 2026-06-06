#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    i64 mx = 0;
    i64 k = 0;

    for(int i = 1; i <= n; i++) {
        k = max(k, mx - a[i]);
        mx = max(mx, a[i]);
    }

    mx = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] < mx) {
            a[i] += k;
        }
        mx = max(mx, a[i]);
    }

    mx = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] < mx) {
            cout << "NO\n";
            return;
        }
        mx = max(mx, a[i]);
    }

    cout << "YES\n";
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