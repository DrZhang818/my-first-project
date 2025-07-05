#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2050/problem/E
/*
    动态规划(经典线性DP LCS) 
    dp[i][j] := 字符串a前i个字符, 字符串b前j个字符构成字符串c的前i + j个字符的最小费用
    第i + j个字符可能由a转移, 也可能由b转移, 因此只需要两个状态取最小值即可
*/
void solve(){
    string a, b, c;
    cin >> a >> b >> c;
    int n = a.length(), m = b.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
    dp[0][0] = 0;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(i < n){
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + (a[i] != c[i + j])); 
            }
            if(j < m){
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + (b[j] != c[i + j]));
            }
        }
    }
    cout << dp[n][m] << "\n";
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