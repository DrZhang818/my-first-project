#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;

//https://www.luogu.com.cn/problem/P4124
constexpr int N = 15;
vector<int> num(N);
ll dp[N][11][11][2][2][2];
ll dfs(int pos, int pre, int ppre, bool ok, bool has4, bool has8, bool lead, bool lim) {
    if(pos == 0) return ok && !(has4 && has8);
    ll &res = dp[pos][pre][ppre][ok][has8][has4];
    if(!lead && !lim && res != -1) return res;
    ll ans = 0;
    int up = (lim ? num[pos] : 9);
    for(int i = 0; i <= up; i++) {
        if(i == 0 && lead) continue;
        else if(i == pre && i == ppre) {
            ans += dfs(pos - 1, i, pre, true, has4 || i == 4, has8 || i == 8, false, lim && i == up);
        }
        else {
            ans += dfs(pos - 1, i, pre, ok, has4 || i == 4, has8 || i == 8, false, lim && i == up);
        }
    }
    if(!lead && !lim) {
        res = ans;
    }
    return ans;
} 
ll work(ll x) {
    int cnt = 0;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    memset(&dp, -1, sizeof(dp));
    if(cnt < 11) return 0;
    return dfs(cnt, 10, 10, false, false, false, true, true);
}
void solve() { 
    ll a, b;
    cin >> a >> b;
    cout << work(b) - work(a - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
