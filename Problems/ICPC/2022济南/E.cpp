#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    i64 n, k;
    cin >> n >> k;
    
    i64 m = n % k == 0 ? k : n % k;
    i64 n2 = n / 2;

    i64 x = (n + k - 1) / k;
    i64 t = (n2 + x - 1) / x;
    i64 y = x * t;
    bool ok = false;

    if(m * x >= n2) {
        ok |= (y - n2 <= min(t, k - m));
    }

    if(x - 1 != 0) {
        t = min(n2 / (x - 1), k - m);
        y = (x - 1) * t;
        ok |= (n2 - y <= min(m, t));
    }

    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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