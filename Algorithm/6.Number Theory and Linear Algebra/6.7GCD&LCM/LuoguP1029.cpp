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
    int G, L;
    cin >> G >> L;
    int MX = L;
    if(L % G != 0) {
        cout << 0 << "\n";
        return;
    }
    L /= G;
    vector<ll> cnt;
    for(int i = 2; i <= L; i++) {
        ll c = 0;
        while(L % i == 0) {
            c += 1;
            L /= i;
        }
        if(c) cnt.push_back(c);
    }
    if(L > 1) cnt.push_back(1);
    ll ans = 1;
    for(int i = 0; i < cnt.size(); i++) {
        ll x = cnt[i];
        ans *= power(x + 1, 2) - 2 * power(x, 2) + power(x - 1, 2);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
