#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

i64 norm(i64 x, i64 m) {
    return (x % m + m) % m;
}

void solve() {
    i64 n, m;
    cin >> n >> m;

    i64 sum = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
    }
    sum %= m;

    i64 T = n * (n + 1) / 2;

    i64 u, v;
    i64 g = exgcd(n, T, u, v);

    i64 x, y;
    i64 p = exgcd(g, m, x, y);

    i64 r = sum % p;
    i64 k = norm(x * ((r - sum) / p), m);
    i64 s = norm(u * k, m);
    i64 d = norm(v * k, m);

    cout << r << "\n";
    cout << s << " " << d << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
