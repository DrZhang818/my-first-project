#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n, k;
    cin >> n >> k;
    while(~n & 1) n >>= 1;
    ll ans = 0;
    int cnt = __builtin_popcountll(n);
    int tot = __lg(n) + 1;
    if(tot - cnt + 1 <= k) {
        ans = tot + k - 1 - (tot - cnt);
        cout << ans << "\n";
        return;
    } 
    vector<array<int,32>> dp(32);
    for(int i = 0; i < 32; i++) {
        fill(dp[i].begin(), dp[i].end(), -inf);
    }
    dp[0][k] = 0;
    for(int i = 30; i >= 0; i--) {
        vector<array<int,32>> ndp(32);
        for(int j = 0; j < 32; j++) {
            fill(ndp[j].begin(), ndp[j].end(), -inf);
        }
        int x = n >> i & 1;
        for(int j = 0; j <= 30; j++) {
            for(int w = 0; w <= k; w++) {
                if(dp[j][w] == -inf) continue;
                if(x == 1) {
                    ndp[j + 1][w] = max(ndp[j + 1][w], dp[j][w]);
                    if(w > 0) {
                        ndp[0][w - 1] = max(ndp[0][w - 1], dp[j][w] + j + 1);
                    }
                } else {
                    ndp[0][w] = max(ndp[0][w], dp[j][w]);
                    if(w > 0) {
                        ndp[j + 1][w - 1] = max(ndp[j + 1][w - 1], dp[j][w]);
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    for(int i = 0; i < 32; i++) {
        ans = max(ans, (ll)dp[i][0]);
    }
    cout << ans << "\n";
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
