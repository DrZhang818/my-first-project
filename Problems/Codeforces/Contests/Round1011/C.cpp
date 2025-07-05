#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    ll x, y;
    cin >> x >> y;
    if(x == y) {
        cout << -1 << "\n";
        return;
    }
    ll ans = 0;
    for(int i = 0; i < 30; i++) {
        if((x & y) == 0) break;
        if((x >> i & 1) && (y >> i & 1)) {
            ll cur = 0;
            int j = i - 1;
            for(; j >= 0; j--) {
                cur += (1 << j);
                if((x >> j & 1) ^ (y >> j & 1)) {
                    break;
                }
            }
            if(j == -1) {
                cur = (1 << i);
            }
            ans += cur;
            x += cur;
            y += cur;
        }
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
    
