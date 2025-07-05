#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2061/problem/C
/*
    状态机DP
    题意:
        给定长度为n的数组, 任意位置i都拥有"诚实"和"说谎"两种状态
        当位置i为"诚实"时, a[:i-1]必须恰好有a[i]个"说谎"的状态
        当位置i为"说谎"时, a[:i-1]不一定恰有a[i]个"说谎"的状态
        问共有多少种合法方案
*/
const int MOD = 998244353;
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<ll>> dp(2, vector<ll>(2));
    dp[0][0] = 1;
    dp[0][1] = a[0] == 0;
    for(int i = 1; i < n; i++){
        if(i == 1){
            dp[1][0] = dp[0][1];
            if(a[1] == 0) dp[1][1] = dp[0][1];
            if(a[1] == 1) dp[1][1] = dp[0][0];
        }
        else{
            dp[i%2][0] = dp[(i-1)%2][1];
            dp[i%2][1] = 0;
            if(a[i-2] + 1 == a[i]) dp[i%2][1] += dp[(i-1)%2][0];
            if(a[i-1] == a[i]) dp[i%2][1] += dp[(i-1)%2][1];
        }
        dp[i%2][0] %= MOD;
        dp[i%2][1] %= MOD;
    }
    cout << (dp[(n-1)%2][0] + dp[(n-1)%2][1]) % MOD << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}