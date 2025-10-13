#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    map<int,ll> mp;
    for(int i = 0; i < m; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        if(l == r) {
            continue;
        }
        mp[l] += c;
        mp[r] -= c;
    }
    if(mp[1] == 0) {
        cout << 0 << "\n";
        return;
    }
    ll ans = numeric_limits<ll>::max();
    ll sum = 0;
    for(auto [x, c] : mp) {
        if(x == n) break;
        sum += c;
        ans = min(ans, sum);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); 

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
