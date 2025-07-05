#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    if(b == 0) {
        a = max(1LL, a);
        cout << n * a << "\n";
        return;
    }
    auto get = [&](ll u, ll v) -> ll {
        return (a + b * v) * u + v;
    };
    ll x = (a + b * n - 1) / (2 * b);
    if(x >= n) x = n - 1;
    ll ans = max(get(x, n - x), get(x + 1, n - x - 1));
    cout << ans << "\n"; 
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
