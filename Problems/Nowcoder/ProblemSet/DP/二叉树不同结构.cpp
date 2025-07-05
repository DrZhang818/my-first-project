#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea
constexpr int MOD = 1e9 + 7;
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> dp(2, vector<ll>(n + 1, 0));
    dp[0][0] = dp[1][0] = 1;
    for(int j = 1; j <= m; j++){
        for(int i = 1; i <= n; i++){
            dp[j % 2][i] = 0;
            for(int k = 0; k <= i - 1; k++){
                dp[j % 2][i] = (dp[j % 2][i] + dp[(j + 1) % 2][k] * dp[(j + 1) % 2][i - 1 - k] % MOD) % MOD;
            }
        }
    }
    cout << dp[m % 2][n] << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}