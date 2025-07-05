#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



const int MOD = 1e9 + 7;
void solve(){ 
    string s;
    cin >> s;
    vector<ll> dp(2);
    dp[0] = 3;
    ll cnt = 2;
    for(int i = 1; i < s.size(); i++) {
        ll &cur = dp[i % 2], &pre = dp[(i + 1) % 2];
        if(s[i] == '1') {
            cur = pre * 3 % MOD;
            cnt = cnt * 2 % MOD;
        } else {
            cur = (pre * 3 % MOD - cnt * 2 % MOD + MOD) % MOD;
        }
    }
    cout << dp[(s.size() - 1) % 2] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

