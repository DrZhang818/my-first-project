#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int a[505], b[505], dp[505][505];
signed main() {
    ios::sync_with_stdio(0); 
    cin.tie(0);
    int n, m, cnt=0, summ=0; 
    cin >> n >> m; 
    for (int i=1; i<=n; i++) {
        cin >> a[i]; 
    }
    for (int j=1; j<=m; j++) {
        cin >> b[j];
    }
    for (int i=1; i<=500; i++) {
        dp[0][0] = 1; 
        cnt=0;
        for (int j=1; j<=m; j++) {
            while (a[cnt+1] + i <= b[j] && cnt+1 <= n) {
                cnt++; 
            }
            for (int k=0; k<=j; k++) {
                dp[j][k] = (dp[j-1][k] + (k == 0 ? 0 : dp[j-1][k-1]) * max(cnt - (k-1), 0ll) % 998244353) % 998244353; 
                if (j == m && k) (summ += dp[j][k]) %= 998244353;
            }
        }
    }   
    cout << summ;
}