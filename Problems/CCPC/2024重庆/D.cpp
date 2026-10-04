#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
i64 mod_inv(i64 a, i64 p) {
    i64 x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

void solve() {
    i64 a, b;
    cin >> a >> b;

    i64 m = b;
    while(m % 2 == 0) m >>= 1;
    while(m % 5 == 0) m /= 5;
    i64 t = b / m;

    i64 x = m - a * mod_inv(t, m) % m;
    if(x >= m) x -= m;

    i64 C = inf, D = inf;

    for(i64 u = 1; m * u <= inf; u <<= 1) {
        for(i64 v = 1; m * u * v <= inf; v *= 5) {
            i64 c = u * v * x % m;
            i64 d = m * u * v;
            if(c < C) {
                C = c;
                D = d;
            }
        }
    }

    cout << C << " " << D << "\n";

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}