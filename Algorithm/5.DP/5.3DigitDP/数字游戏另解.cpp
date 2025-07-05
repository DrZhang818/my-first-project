#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int N = 15;
vector<int> num(N);
vector<vector<ll>> dp(N, vector<ll>(10, -1));
ll dfs(int pos, int pre, bool lead, bool lim) {
    if(pos == 0) return 1;
    if(!lead && !lim && dp[pos][pre] != -1) return dp[pos][pre];
    ll ans = 0;
    int up = (lim ? num[pos] : 9);
    for(int i = pre; i <= up; i++) {
        if(i == 0 && lead) ans += dfs(pos - 1, i, true, lim && i == up);
        else ans += dfs(pos - 1, i, false, lim && i == up);
    }
    if(!lead && !lim) dp[pos][pre] = ans;
    return ans;
}
ll work(ll x) {
    int cnt = 0;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    for(int i = 0; i < N; i++) for(int j = 0; j < 10; j++) dp[i][j] = -1;
    return dfs(cnt, 0, true, true);
}
void solve(ll l, ll r) { 
    cout << work(r) - work(l - 1) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll a, b;
    while(cin >> a >> b) {
        solve(a, b);
    }
    return 0;
}
    
