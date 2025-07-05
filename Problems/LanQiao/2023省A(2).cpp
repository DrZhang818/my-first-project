#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    ll ans = 2;
    vector<ll> dp(23);
    dp[0] = 1;
    for(int i = 1; i <= 22; i++) {
        dp[i] = dp[i - 1] * 2;
        if(i == 10) {
            dp[i] -= 1;
        } else if (i >= 11) {
            dp[i] -= dp[i - 11];
        }
        ans += dp[i];
    }
    for(int i = 1; i <= 22; i++) {
        cout << dp[i] << "\n";
    }
    cout << ans << "\n";
}
// void solve() {
//     ll ans = 0;
//     auto dfs = [&](auto &&dfs, int cnt, int sum) -> void {
//         if(sum == 100 || cnt >= 31) {
//             return;
//         } 
//         if(sum == 70) ans++;
//         dfs(dfs, cnt + 1, sum + 10);
//         dfs(dfs, cnt + 1, 0);
//     };
//     dfs(dfs, 0, 0);
//     cout << ans << "\n";
// }
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

