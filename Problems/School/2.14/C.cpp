#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



const int MOD = 1e9 + 7;
void solve(){ 
    int n, m;
    cin >> n >> m;
    unordered_map<int,int> mp;
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        mp[x]++;
        if(mp[x - 1]) {
            cout << 0 << "\n";
            return;
        }
    }
    vector<ll> dp(3);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        if(mp[i]) {
            dp[i % 3] = 0;
            continue;
        }
        dp[i % 3] = dp[(i + 1) % 3] + dp[(i + 2) % 3];
        dp[i % 3] %= MOD;
    }
    cout << dp[n % 3] << "\n";

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

