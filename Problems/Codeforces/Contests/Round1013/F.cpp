#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

//https://codeforces.com/problemset/problem/2091/F
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() { 
    int n, m, d;
    cin >> n >> m >> d;
    int r = d - 1;
    vector a(n  + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> dp(m + 1);
    for(int i = 1; i <= n; i++) {
        vector<int> ndp(m + 1);
        for(int j = 1; j <= m; j++) {
            if(a[i][j] != 'X') continue;
            if(i == 1) ndp[j] = 1;
            else ndp[j] = (dp[min(m, j + r)] - dp[max(0, j - r - 1)] + MOD) % MOD;
        }
        vector<int> pre(m + 1);
        for(int j = 1; j <= m; j++) {
            pre[j] = (pre[j - 1] + ndp[j]) % MOD;
        }
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == 'X') {
                ndp[j] = (pre[min(m, j + d)] - pre[max(0, j - d - 1)] + MOD) % MOD;
            }
        }
        for(int j = 1; j <= m; j++) {
            add(ndp[j], ndp[j - 1]);
        }
        swap(dp, ndp);
    }    
    cout << dp[m] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
