#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int num[60];
int c0[60], c1[60];
ll dp[60][2];
ll dfs(int pos, bool lim) {
    if(pos == -1) {
        return 0;
    }
    ll &res = dp[pos][lim];
    if(res != -1 && !lim) return res;
    ll cur = 0;
    int up = lim ? num[pos] : 1;
    for(int i = 0; i <= up; i++) {
        if(i == 0) cur = max(cur, dfs(pos - 1, lim && i == up) + c1[pos] * (1LL << pos));
        else cur = max(cur, dfs(pos - 1, lim && i == up) + c0[pos] * (1LL << pos));
    }
    if(!lim) res = cur;
    return cur;
} 

ll work(ll x) {
    int c = 0;
    while(x) {
        num[c++] = x & 1;
        x >>= 1;
    }
    return dfs(59, true);
}
void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        for(int j = 0; j < 60; j++) {
            if(a[i] >> j & 1) {
                c1[j]++;
            } else {
                c0[j]++;
            }
        }
    }
    ll ans = work(k);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
