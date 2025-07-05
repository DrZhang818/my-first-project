#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll cal(ll x) {
    x += 1;
    return x & -x;
}
struct info {
    ll x, cnt;
    friend bool operator < (const info &a, const info &b) {
        return a.cnt > b.cnt;
    }
};
void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    priority_queue<info> q;
    for(int i = 1; i <= n; i++) {
        q.push({a[i], cal(a[i])});
    }
    while(k) {
        auto [x, cnt] = q.top(); q.pop();
        if(k < cnt) {
            q.push({x, cnt});
            break;
        }
        x |= cnt;
        k -= cnt;
        q.push({x, cal(x)});
    }
    ll ans = 0;
    while(!q.empty()) {
        auto [x, _] = q.top(); q.pop();
        while(x) {
            ans += x & 1;
            x >>= 1;
        }
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
