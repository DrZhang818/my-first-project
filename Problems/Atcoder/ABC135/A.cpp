#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 1000000007;
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    vector<ll> dp(13);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        vector<ll> ndp(13);
        char c = s[i];
        if(c != '?') {
            int x = c - '0';
            for(int i = 0; i <= 12; i++) {
                ndp[(i * 10 + x) % 13] = dp[i];
            }
        } else {
            for(int x = 0; x <= 9; x++) {
                for(int i = 0; i <= 12; i++) {
                    ndp[(i * 10 + x) % 13] += dp[i];
                    ndp[(i * 10 + x) % 13] %= MOD;
                }
            }
        }
        dp = ndp;
    }
    cout << dp[5] << "\n";
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
