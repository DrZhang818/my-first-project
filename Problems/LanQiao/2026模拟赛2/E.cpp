#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;

int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> x(n + 1), y(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }    
    vector<int> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i] = 1LL * (dp[i - 1] + 1) * y[i] % MOD * power(y[i] - x[i], MOD - 2) % MOD;
    }
    cout << dp[n] << "\n";
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