#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.acwing.com/problem/content/6028/
constexpr int inf = 1000000000;
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(3, vector<int>(2, 0)));
    for(int j = 0; j <= 2; j++) dp[0][j][1] = -inf;

    for(int i = 1; i <= n; i++) {
        auto &pre = dp[(i - 1) % 2], &cur = dp[i % 2];
        for(int j = 1; j <= 2; j++) {
            cur[j][0] = max(pre[j][0], pre[j][1] + a[i]);
            cur[j][1] = max(pre[j - 1][0] - a[i], pre[j][1]);
        }
    }
    cout << dp[n % 2][2][0] << "\n"; 
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
    
