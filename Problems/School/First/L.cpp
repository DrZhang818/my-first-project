#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    map<ll,ll> mp;
    for(int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        mp[x]++;
    }
    int q;
    cin >> q;
    while(q--) {
        ll x, y;
        cin >> x >> y;
        if(x * x - 2 * y <= 0 || x * x - 4 * y < 0) {
            cout << 0 << " ";
            continue;
        } 
        if(abs(sqrt(x * x - 4 * y) - (ll)sqrt(x * x - 4 * y)) > 1e-7) {
            cout << 0 << " ";
            continue;
        }
        ll del = (ll)sqrt(x * x - 4 * y);
        ll ans = 0;
        if((x + del) % 2 != 0) {
            cout << 0 << " ";
            continue;
        }
        ll a = (x + del) / 2, b = (x - del) / 2;
        if(y % a == 0 && x - a == y / a) {
            if(a == x - a) {
                ans += mp[a] * (mp[a] - 1) / 2;
            } else {
                ans += mp[a] * mp[x - a];
            }
        }
        cout << ans << " ";
    }
    cout << "\n";
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
    
