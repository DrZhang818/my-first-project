#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2070/problem/D

constexpr int MOD = 998244353;
void solve() { 
    int n;
    cin >> n;
    vector<int> fa(n + 1), dep(n + 1);
    for(int i = 2; i <= n; i++) {
        cin >> fa[i];
        dep[i] = dep[fa[i]] + 1;
    }
    vector<int> dp(n + 1);
    vector<vector<int>> nodes(n + 1);
    for(int i = 1; i <= n; i++) {
        nodes[dep[i]].push_back(i);
    }
    ll ans = 1;
    dp[1] = 1;
    ll sum = 1;
    for(int d = 1; d < n; d++) {
        ll nsum = 0;
        for(int v : nodes[d]) {
            dp[v] = sum;
            if(d > 1) {
                dp[v] = (dp[v] - dp[fa[v]] + MOD) % MOD;
            }
            nsum = (nsum + dp[v]) % MOD;
        }
        sum = nsum;
        ans = (ans + sum) % MOD;
    }
    cout << ans << "\n";
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
    
