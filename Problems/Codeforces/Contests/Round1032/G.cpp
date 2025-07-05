#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2121/problem/G
vector<ll> tr;
ll n;
void add(ll o, ll d) {
    for(; o <= 2 * n + 1; o += o & -o) {
        tr[o] += d;
    }
}
ll query(ll o) {
    ll res = 0;
    for(; o > 0; o -= o & -o) {
        res += tr[o];
    }
    return res;
}
void solve() {
    cin >> n;
    tr.assign(2 * n + 2, 0);
    string s;
    cin >> s;
    s = "#" + s;
    vector<ll> pre(n + 1);
    for(ll i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (s[i] == '1' ? 1 : -1);
    }
    ll ans = 0;
    add(n + 1, 1);
    vector<ll> dp(n + 1);
    for(ll i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if(s[i] == '1') {
            dp[i] += query(pre[i] + n);
        } else {
            dp[i] += i - query(pre[i] + n + 1);
        }
        add(pre[i] + n + 1, 1);
        ans += dp[i];
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
