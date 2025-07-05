#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr ll MOD = 998244353;
ll power(ll a, ll b) {
    ll res = 1;
    while(b > 0) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}
void solve() { 
    ll n, G, L;
    cin >> G >> L >> n;
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
        ll ways = ((power(cnt + 1, n) - 2 * power(cnt, n) % MOD) % MOD + power(cnt - 1, n)) % MOD;        
        if(ways < 0) ways += MOD;
        ans = ans * ways % MOD;
    }
    cout << ans % MOD << "\n";
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
    
