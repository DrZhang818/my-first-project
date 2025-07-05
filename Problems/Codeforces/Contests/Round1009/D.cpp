#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<ll> x(n + 1), r(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    map<ll,ll> mp;
    for(int i = 1; i <= n; i++) {
        ll c = x[i], tr = r[i];
        for(int j = c - tr; j <= c + tr; j++) {
            ll delta = j - c;
            mp[j] = max(mp[j], 2 * (ll)sqrt(tr * tr - delta * delta) + 1);
        }
    }
    ll ans = 0;
    for(auto [_, c] : mp) {
        ans += c;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
