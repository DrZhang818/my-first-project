#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    string s;
    cin >> s;
    vector<int> dp(3);
    int cnt = 1;
    for(char c : s) {
        auto ndp = dp;
        if(c == 'A') {
            add(ndp[0], cnt);
        } else if(c == 'B') {
            add(ndp[1], dp[0]);
        } else if(c == 'C') {
            add(ndp[2], dp[1]);
        } else {
            ndp[0] = 3LL * dp[0] % MOD;
            ndp[1] = 3LL * dp[1] % MOD;
            ndp[2] = 3LL * dp[2] % MOD;
            add(ndp[0], cnt);
            add(ndp[1], dp[0]);
            add(ndp[2], dp[1]);
            cnt = 3LL * cnt % MOD;
        }
        swap(dp, ndp);
    }    
    cout << dp[2] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
