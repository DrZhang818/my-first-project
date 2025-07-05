#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int N = 10;
vector<ll> num(N);
vector<ll> dp(N, -1);
ll dfs(int pos, bool lead, bool lim) {
    if(pos == 0) return 1;
    if(!lead && !lim && dp[pos] != -1) return dp[pos];
    ll ans = 0;
    int up = (lim ? num[pos] : 9);
    for(int i = 0; i <= up; i++) {
        if(i == 0 && lead) ans += dfs(pos - 1, true, lim && i == up);
        else if(i % 2 != pos % 2) continue;
        else ans += dfs(pos - 1, false, lim && i == up); 
    }
    if(!lead && !lim) dp[pos] = ans;
    return ans;
}
void solve() { 
    int x;
    cin >> x;
    int cnt = 0;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    cout << dfs(cnt, true, true) - 1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
