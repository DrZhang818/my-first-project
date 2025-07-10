#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    auto get = [&](ll R, ll x, ll y) -> ll {
        ll c1 = R / x, c2 = R / y, c3 = R / lcm(x, y);
        return R - c1 - c2 + c3;
    };
    cout << get(b, c, d) - get(a - 1, c, d) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
