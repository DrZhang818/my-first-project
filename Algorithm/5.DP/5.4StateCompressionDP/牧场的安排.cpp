#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int MOD = 100000000;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> mp(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if(x) mp[i] |= (1 << m - j);
        }
    }    
    vector<int> a;
    for(int i = 0; i < 1 << m; i++) {
        if(i & i >> 1) continue;
        a.push_back(i);
    }
    int cnt = a.size();
    vector dp(n + 2, vector<ll>(1 + (1 << m)));
    dp[0][0] = 1;
    for(int i = 1; i <= n + 1; i++) {
        for(int cur = 0; cur < cnt; cur++) {
            int s = a[cur];
            if((s & mp[i]) != s) continue; 
            for(int pre = 0; pre < cnt; pre++) {
                int ps = a[pre];
                if(s & ps) continue;
                dp[i][cur] += dp[i - 1][pre];
                dp[i][cur] %= MOD;
            }
        }
    }
    cout << dp[n + 1][0] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
