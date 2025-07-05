#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<int> a, b;
    for(int i = 0; i < 1 << n; i++) {
        if(i & (i >> 1)) continue;
        a.push_back(i);
        b.push_back(__builtin_popcount(i));
    }
    int cnt = a.size();
    vector dp(n + 2, vector<vector<ll>>(k + 1, vector<ll>(cnt + 1)));
    dp[0][0][0] = 1;
    for(int i = 1; i <= n + 1; i++) {
        for(int j = 0; j <= k; j++) {
            for(int cur = 0; cur < cnt; cur++) {
                for(int pre = 0; pre < cnt; pre++) {
                    int s = a[cur], ps = a[pre];
                    if(s & ps || s & ps << 1 || s & ps >> 1 || j - b[cur] < 0) continue;
                    dp[i][j][cur] += dp[i - 1][j - b[cur]][pre];
                }
            }
        }
    }
    cout << dp[n + 1][k][0] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
