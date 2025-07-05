#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    ll l, r;
    cin >> l >> r;
    ll nl = l % 2019;
    ll nr = r % 2019;
    if(l / 2019 != r / 2019) {
        cout << 0 << "\n";
        return;
    }
    ll ans = 20000;
    for(ll i = nl; i <= nr; i++) {
        for(ll j = i + 1; j <= nr; j++) {
            ans = min(ans, (i * j) % 2019);
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

