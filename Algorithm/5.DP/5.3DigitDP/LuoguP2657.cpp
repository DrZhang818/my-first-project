#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P2657
constexpr int N = 11;
vector<int> num(N);
vector<vector<ll>> dp(N, vector<ll>(10, -1));
ll dfs(int pos, int pre, bool head, bool lim) {
    if(pos == 0) return 1;
    if(!head && !lim && dp[pos][pre] != -1) return dp[pos][pre];
    ll ans = 0;
    int up = (lim ? num[pos] : 9);
    for(int i = 0; i <= up; i++) {
        if(!head && abs(i - pre) < 2) continue;
        if(i == 0 && head) ans += dfs(pos - 1, i, true, lim && i == up);
        else ans += dfs(pos - 1, i, false, lim && i == up);
    }
    if(!head && !lim) dp[pos][pre] = ans;
    return ans;
}
ll work(int x) {
    int cnt = 0;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    for(int i = 1; i < N; i++) for(int j = 0; j <= 9; j++) dp[i][j] = -1;
    return dfs(cnt, 0, true, true);
}
void solve() { 
    int a, b;
    cin >> a >> b;
    cout << work(b) - work(a - 1) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
