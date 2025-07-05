#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


ll count(ll x) {
    if(x < 10) return x;
    ll t = x, rem = 0;
    while(x) {
        rem += x % 10;
        x /= 10;
    }
    return t + count(rem);
}
int num[15], cnt = 0;
ll memo[15][110][110];
ll dfs(int pos, int tar, int sum, bool lead, bool lim) {
    if(pos == 0) return sum == tar;
    ll &res = memo[pos][tar][sum];
    if(res != -1 && !lead && !lim) return res;
    int up = lim ? num[pos] : 9;
    ll ans = 0;
    for(int i = 0; i <= up; i++) {
        if(lead && i == 0) ans += dfs(pos - 1, tar, sum, true, lim && i == up);
        else if(sum + i <= tar) ans += dfs(pos - 1, tar, sum + i, false, lim && i == up);
    }
    if(!lead && !lim) res = ans;
    return ans;
}
bool work(ll x, ll tar) {
    cnt = 0;
    int t = x;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    ll res = 0;
    for(int i = 1; i <= 108; i++) {
        if(i < 10) res += count(i) * max(0LL, dfs(cnt, i, 0, true, true) - 1);
        else res += count(i) * dfs(cnt, i, 0, true, true);
        // cerr << i << " " << dfs(cnt, i, 0, true, true) << "\n";
    }
    return res >= tar;
}
void solve() { 
    ll n;
    cin >> n;
    ll l = 0, r = 1e12;
    while(l + 1 < r) {
        ll mid = l + r >> 1;
        if(work(mid, n)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(memo, -1, sizeof(memo));
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
