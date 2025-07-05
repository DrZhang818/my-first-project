#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    ll a, b;
    cin >> a >> b;
    ll t = __gcd(a, b);
    ll m = a / t, n = b / t;
    ll ans = 0;
    for(ll x = 0; x <= b - 1; x += t){
        ll k = x / t + m;
        if(__gcd(k, n) == 1){
            ans++;
        }
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