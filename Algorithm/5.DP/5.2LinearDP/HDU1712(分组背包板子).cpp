#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(int n, int m) { 
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> dp(m + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = m; j >= 1; j--) {
            for(int k = 1; k <= j; k++) {
                dp[j] = max(dp[j], dp[j - k] + a[i][k]);
            }
        }
    }
    cout << dp[m] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while(cin >> n >> m && n) {
        solve(n, m);
    }
    return 0;
}

