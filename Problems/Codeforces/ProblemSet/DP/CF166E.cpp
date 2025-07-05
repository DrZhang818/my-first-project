#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int MOD = 1000000007;
void solve() { 
    int n;
    cin >> n;
    vector<ll> dp(4);
    dp[3] = 1;
    for(int i = 1; i <= n; i++) {
        vector<ll> ndp(4);
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                if(k == j) continue;
                ndp[j] += dp[k];
            }
            ndp[j] %= MOD;
        }
        dp = ndp;
    }
    cout << dp[3] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
