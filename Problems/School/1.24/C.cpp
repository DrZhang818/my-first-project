#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int n;
    cin >> n;
    vector<ll> a(n);
    auto lcm = [&](ll a, ll b) -> ll{
        ll g = __gcd(a, b);
        return a / g * b;
    };
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll ans = 1;
    for(int i = 0; i < n; i++){
        ans = lcm(ans, a[i]);
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