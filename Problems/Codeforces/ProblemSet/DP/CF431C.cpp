#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/problemset/problem/431/C
constexpr ll MOD = 1000000007;
//正解: O(n^2)   转化为状态机DP
void solve1() {
    int n, k, d;
    cin >> n >> k >> d;
    vector dp(n + 1, vector<ll>(2));
    dp[0][0] = 1, dp[0][1] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= min(i, k); j++) {
            if(j < d) {
                dp[i][0] = (dp[i][0] + dp[i - j][0]) % MOD;
                dp[i][1] = (dp[i][1] + dp[i - j][1]) % MOD;
            } else {
                dp[i][1] = (dp[i][1] + dp[i - j][0] + dp[i - j][1]) % MOD; 
            }
        }
    }
    cout << dp[n][1] << "\n";
}
//自己的做法: O(n^3)   建模为分组01背包 + 容斥原理
void solve2() { 
    int n, k, d;
    cin >> n >> k >> d;
    auto work = [&](int up) -> ll {
        ll res = 0;
        vector dp(n + 1, vector<ll>(n + 1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                for(int p = 1; p <= up && p <= j; p++) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - p]) % MOD;
                }
            }
        }
        for(int i = 1; i <= n; i++) res = (res + dp[i][n]) % MOD;
        return res;
    };
    ll ans = ((work(k) - work(d - 1)) % MOD + MOD) % MOD;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve1();
    return 0;
}
    
