#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll len[19];
int num[19];
ll dp[19][180][2][2];
ll dfs(int pos, int s, bool lead, bool lim) {
    if(pos == 0) {
        return s;
    }
    ll &res = dp[pos][s][lead][lim];
    if(res != -1 && !lead && !lim) return res;
    ll cur = 0;
    int up = lim ? num[pos] : 9;
    for(int i = 0; i <= up; i++) {
        if(lead && i == 0) cur += dfs(pos - 1, s + i, true, lim && i == up);
        else cur += dfs(pos - 1, s + i, false, lim && i == up);
    }
    if(!lead && !lim) res = cur;
    return cur;
}
ll work(ll x) {
    int cnt = 0;
    while(x) {
        num[++cnt] = x % 10;
        x /= 10;
    }
    return dfs(cnt, 0, true, true);
}
void solve() {
    ll k;
    cin >> k;
    ll x = 1, p;
    for(int i = 1; i <= 18; i++) {
        if(k > len[i]) {
            k -= len[i];
            x *= 10;
        } else {
            p = i;
            break;
        }
    }
    ll d = k / p;
    k %= p;
    x += d;
    ll ans = 0;
    string s = to_string(x);
    for(int i = 0; i < k; i++) {
        ans += s[i] - '0';
    }
    ans += work(x - 1);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));
    len[0] = 0;
    ll cur = 9;
    for(int i = 1; i <= 18; i++) {
        len[i] = cur * i;
        cur *= 10;
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
