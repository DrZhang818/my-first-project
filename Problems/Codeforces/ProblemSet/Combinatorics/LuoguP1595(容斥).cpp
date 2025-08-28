#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll fac[21];
void solve() {
    int n;
    cin >> n;
    ll ans = 0;
    for(int i = 0, tag = 1; i <= n; i++, tag ^= 1) {
        ll cur = fac[n] / fac[i];
        if(tag) {
            ans += cur;
        } else {
            ans -= cur;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= 20; i++) {
        fac[i] = fac[i - 1] * i;
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
