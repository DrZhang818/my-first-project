#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://loj.ac/p/10148
void solve() { 
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    vector dp(2 * n + 1, vector<int>(2 * n + 1));
    int ans = 0;
    for(int len = 3; len <= n + 1; len++) {
        for(int i = 1; i + len - 1 <= 2 * n; i++) {
            int j = i + len - 1;
            dp[i][j] = -1;
            for(int k = i + 1; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + a[i] * a[k] * a[j]);
            }
            if(len == n + 1) ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
