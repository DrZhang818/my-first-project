#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> dp(2, vector<int>(n + 1));
    for(int i = n - 1; i >= 0; i--) {
        auto &pre = dp[(i + 1) % 2], &cur = dp[i % 2];
        for(int j = 0; j <= i; j++) {
            cur[j] = max(pre[j], pre[j + 1]) + a[i][j];
        }
    }
    cout << dp[0][0] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
