#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
constexpr int inf = 1000000000;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> mp(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if(c == 'P') {
                mp[i] |= (1 << m - j);
            }
        }
    }    
    vector<int> a, b;
    for(int i = 0; i < 1 << m; i++) {
        if(i & i >> 1 || i & i >> 2) continue;
        a.push_back(i);
        b.push_back(__builtin_popcount(i));
    }
    int cnt = a.size();
    vector dp(2, vector<vector<int>>(cnt + 1, vector<int>(cnt + 1, -inf)));
    dp[0][0][0] = 0;
    for(int i = 1; i <= n + 2; i++) {
        for(int j = 0; j < cnt; j++) {
            int s = a[j];
            if((mp[i] & s) != s) continue;
            for(int k = 0; k < cnt; k++) {
                int ps = a[k];
                if(s & ps) continue;
                for(int m = 0; m < cnt; m++) {
                    int pps = a[m];
                    if(s & pps || ps & pps) continue;
                    dp[i % 2][j][k] = max(dp[i % 2][j][k], dp[(i - 1) % 2][k][m] + b[j]);
                }
            }
        }
    }
    cout << dp[(n + 2) % 2][0][0] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
