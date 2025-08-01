#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    ll a, b;
    for(int i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        if(i == 1) {
            a = x;
            b = y;
        } else {
            ll t = max((a + x - 1) / x, (b + y - 1) / y);
            a = t * x;
            b = t * y;
        }
    }
    cout << a + b << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
