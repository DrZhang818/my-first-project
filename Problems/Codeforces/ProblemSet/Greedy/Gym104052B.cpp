#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

const int w[][4] = {
    {2, 1, 1, 0},
    {2, 0, 2, 0},
    {1, 1, 2, 1},
};

void solve() {  
    array<int,4> a {};
    for(int i = 0; i < 4; i++) {
        cin >> a[i];
    }

    ll ans = inf;
    for(int s = 0; s < 1 << 4; s++) {
        ll cur = 0;
        for(int i = 0; i < 4; i++) {
            if(s >> i & 1) {
                cur += a[i];
            }
        }

        ll x = inf;
        for(int i = 0; i < 3; i++) {
            ll y = 0;
            for(int j = 0; j < 4; j++) {
                if(s >> j & 1) {
                    y += w[i][j];
                }
            }
            x = min(x, y);
        }

        if(x) {
            ans = min(ans, cur / x);
        }
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
