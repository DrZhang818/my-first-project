#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int MOD = 1e9 + 7;
void solve() { 
    ll n;
    cin >> n;
    vector<ll> dp(n);
    dp[0] = n % MOD;
    dp[1] = n * (n - 1) % MOD;
    vector<ll> ans(n);
    ans[0] = n, ans[1] = n * n;
    for(int i = 2; i <= n - 1; i++) {
        dp[i] = dp[i - 1];
        if(i - n - 2 >= 0) {
            dp[i] -= ans[i - n - 2];
        } else {
            dp[i] -= 1;
        }
        if(i - 3 >= 0) {
            dp[i] += ans[i - 3];
        } else {
            dp[i] += 1;
        }
        dp[i] = (dp[i] + MOD) % MOD;
        ans[i] = (ans[i - 1] + dp[i]) % MOD;
    }
    cout << ans[n - 1] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
