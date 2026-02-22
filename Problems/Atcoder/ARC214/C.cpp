#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int sum = accumulate(a.begin() + 1, a.end(), 0);

    if(sum & 1) {
        cout << 0 << "\n";
        return;
    }

    int tar = sum >> 1;
    vector<int> dp(tar + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        for(int j = 0; j + a[i] <= tar; j++) {
            add(ndp[j + a[i]], dp[j]);
        }
        dp = move(ndp);
    }

    int ans = 1LL * dp[tar] * (dp[tar] - 2) % MOD;
    cout << ans << "\n";
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
