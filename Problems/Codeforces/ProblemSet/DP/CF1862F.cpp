#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int x, y;
    cin >> x >> y;
    int n;
    cin >> n;
    int sum = 0;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    vector<int> dp(sum + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = sum - a[i]; j >= 0; j--) {
            dp[j + a[i]] |= dp[j];
        }
    }

    int ans = inf;
    for(int i = 0; i <= sum; i++) {
        if(dp[i] == 0) continue;
        ans = min(ans, max((i + x - 1) / x, (sum - i + y - 1) / y));
    }
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