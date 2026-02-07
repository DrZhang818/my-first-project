#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(), 
        [&](auto x, auto y) {
            return a[x] < a[y];
        });

    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2));
    for(int len = 1; len <= n; len++) {
        ll v = a[p[len]];
        for(int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if(l == r) {
                dp[l][r] = v * abs(p[len] - l);
            } else {
                dp[l][r] = max(dp[l + 1][r] + v * abs(p[len] - l), dp[l][r - 1] + v * abs(p[len] - r));
            }
        }
    }
    cout << dp[1][n] << "\n";
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
