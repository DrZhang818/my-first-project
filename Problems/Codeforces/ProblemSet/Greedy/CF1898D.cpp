#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9 + 7;

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    i64 ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] > b[i]) {
            swap(a[i], b[i]);
        }
        ans += b[i] - a[i];
    }
    i64 max_a = -inf, min_b = inf;
    i64 add = 0;
    for(int i = 1; i <= n; i++) {
        if(min_b < a[i]) {
            add = max(add, 2LL * (a[i] - min_b));
        }
        if(max_a > b[i]) {
            add = max(add, 2LL * (max_a - b[i]));
        }
        max_a = max(max_a, a[i]);
        min_b = min(min_b, b[i]);
    }
    cout << ans + add << "\n";
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
