#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<ll,ll> PLL;
typedef unsigned long long ull;
const int inf = 1000000000;
const ll MOD = 998244353;
ll n, k;
vector<int> num(61);
PLL dp[61][61];
PLL dfs(int pos, int c, bool lim) {
    if(pos == 0) {
        if(c == 0) return {0, 1};
        return {0, 0};
    }
    if(!lim && dp[pos][c].first != -1) return dp[pos][c];
    int up = lim ? num[pos] : 1;
    PLL res = {0, 0};
    for(ll i = 0; i <= up && i <= c; i++) {
        PLL tmp = dfs(pos - 1, c - i, lim && i == up);
        res = {(res.first + (i << pos - 1) % MOD * tmp.second % MOD + tmp.first) % MOD, (res.second + tmp.second) % MOD};
    }
    if(!lim) dp[pos][c] = res;
    return res;
}
ll work(ll x) {
    int cnt = 0;
    while(x) {
        num[++cnt] = x & 1;
        x >>= 1;
    }
    PLL ans = dfs(cnt, k, true);
    return ans.first;
}

void solve() {
    cin >> n >> k;
    cout << work(n) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= 60; i++) {
        for(int j = 0; j <= 60; j++) {
            dp[i][j] = {-1, -1};
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}