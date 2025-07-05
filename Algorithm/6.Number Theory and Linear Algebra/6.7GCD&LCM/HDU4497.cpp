#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


ll power(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
void solve() { 
    ll G, L;
    cin >> G >> L;
    if(L % G != 0) {
        cout << 0 << "\n";
        return;
    }
    L /= G;
    vector<ll> c;
    for(int i = 2; i * i <= L; i++) {
        ll t = 0;
        while(L % i == 0) {
            t += 1;
            L /= i;
        }
        if(t > 0) c.push_back(t);
    }
    if(L > 1) c.push_back(1);
    ll ans = 1;
    for(int i = 0; i < c.size(); i++) {
        ll cnt = c[i];
        ll ways = power(cnt + 1, 3) - 2 * power(cnt, 3) + power(cnt - 1, 3);        
        ans = ans * ways;
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
    
