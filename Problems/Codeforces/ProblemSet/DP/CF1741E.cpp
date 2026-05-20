#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> dp(n + 1);
    dp[0] = 1;
    for(int i = 0; i <= n; i++) {
        if(i && i - a[i] - 1 >= 0) dp[i] |= dp[i - a[i] - 1];
        if(i < n && i + 1 + a[i + 1] <= n) dp[i + 1 + a[i + 1]] |= dp[i];
    }

    if(dp[n]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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