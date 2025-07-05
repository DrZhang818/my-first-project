#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve(){ 
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }   
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> pre(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i] == b[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                pre[i][j] = 1;
            } else {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
                pre[i][j] = dp[i][j - 1] > dp[i - 1][j] ? 2 : 3;
            }
        }
    }
    int ans = dp[n][n];
    vector<int> LCS(ans);
    int x = n, y = n;
    while(ans) {
        if(pre[x][y] == 1) {
            LCS[--ans] = a[x];
            x--, y--;
        }
        else if(pre[x][y] == 2) {
            y--;
        }
        else {
            x--;
        }
    }
    for(auto c : LCS) {
        cout << c << " ";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
