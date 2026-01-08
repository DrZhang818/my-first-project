#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

void add(int &x, int y) {
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
    sort(a.begin() + 1, a.end());
    vector<int> dp(sum + 1);
    dp[0] = 1;
    int ans = 0; 
    for(int i = 1; i <= n; i++) {
        for(int j = sum - a[i]; j >= 0; j--) {
            add(dp[j + a[i]], dp[j]);
            add(ans, 1LL * dp[j] * max((j + a[i] + 1) / 2, a[i]) % MOD);
        }
    }
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
