#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr ll MOD = 1000000007;
constexpr int N = 100005;
int t, k;
vector<vector<int>> dp(N + 1, vector<int>(2));
vector<ll> pre(N + 1);
void solve() { 
    int a, b;
    cin >> a >> b;
    cout << ((pre[b] - pre[a - 1]) % MOD + MOD) % MOD << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> t >> k;
    dp[0][0] = 1;
    ll x = 0, y = 0;
    for(int i = 1; i <= N; i++) {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % MOD;
        if(i >= k) dp[i][1] = (dp[i - k][0] + dp[i - k][1]) % MOD;
    }
    for(int i = 1; i <= N; i++) {
        pre[i] = pre[i - 1] + dp[i][0] + dp[i][1];
        pre[i] %= MOD;
    }
    while(t--) {
        solve();
    }
    return 0;
}
    
