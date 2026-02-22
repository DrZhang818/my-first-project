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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> sum(k + 1);
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));

    sum[0] = 1;

    for(int i = 1; i <= n; i++) {
        int x = a[i];
        vector<int> ndp(k + 1);
        for(int j = 0; j <= k; j++) {
            add(ndp[j], sum[j]);
            if(j >= 1) {
                add(ndp[j], dp[x][j - 1]);
            }
        }
        for(int j = 0; j <= k; j++) {
            add(sum[j], (ndp[j] - dp[x][j] + MOD) % MOD);
        }
        dp[x] = move(ndp);
    }

    cout << sum[k] << "\n";
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
