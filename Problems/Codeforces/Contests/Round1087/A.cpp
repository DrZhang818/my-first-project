#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    i64 n, cur, k;
    cin >> n >> cur >> k;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    for(int i = 1; i <= n; i++) {
        if(cur < a[i]) break;
        int d = min(cur - a[i], k);
        a[i] += d;
        k -= d;
        cur += a[i];
    }
    cout << cur << "\n";
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
