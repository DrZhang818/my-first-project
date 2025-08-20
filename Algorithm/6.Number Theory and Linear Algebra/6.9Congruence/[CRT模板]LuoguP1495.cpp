#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
i128 inv(i128 a, i128 p) {
    i128 x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), m(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> m[i] >> a[i];
    }
    i128 M = 1;
    for(int i = 1; i <= n; i++) {
        M *= m[i];
    }
    i128 x = 0;
    for(int i = 1; i <= n; i++) {
        i128 cur = M / m[i];
        x = (x + a[i] * cur % M * inv(cur, m[i]) % M) % M;
    }
    ll ans = x;
    cout << ans << "\n";
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
