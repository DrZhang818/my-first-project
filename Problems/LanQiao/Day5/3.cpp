#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


const int MOD = 1000000007;
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    ll ans = 0;
    ll sum = 0;
    for(auto c : s){
        sum += c - 'a' + 1;
    }
    // vector<vector<ll>> memo(sum + 1, vector<ll>(n + 1, -1));
    vector<vector<ll>> dp(27, vector<ll>(n + 1));
    const int m = 27;
    for(int i = 0; i <= sum; i++){
        for(int j = 1; j <= n; j++){
            if(i / j < 1 || i / j > 26){
                continue;
            }
            if(j == 1){
                dp[i%m][j] = 1;
                continue;
            }
            dp[i%m][j] = 0;
            for(int k = 1; k <= min(26,i); k++){
                dp[i%m][j] = (dp[i%m][j] + dp[(i - k + m)%m][j - 1]) % MOD;
            }
        }
    }
    ans = dp[sum%m][n];
    // auto dfs = [&](auto&& dfs, ll s, int n) -> ll{
    //     if(s / n < 1 || s / n > 26){
    //         return 0;
    //     }
    //     if(n == 1){
    //         return 1;
    //     }
    //     ll &res = memo[s][n];
    //     if(res != -1) return res;
    //     res = 0;
    //     for(int i = 1; i <= 26; i++){
    //         res = (res + dfs(dfs, s - i, n - 1)) % MOD;
    //     }
    //     return res;
    // };
    // ans = dfs(dfs, sum, n) % MOD;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}