#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

// 二项式反演
void solve() {
    i64 a, b, c, m;
    cin >> a >> b >> c >> m;

    i64 n_a = m / a;
    i64 n_b = m / b;
    i64 n_c = m / c;
    i64 n_ab = m / lcm(a, b);
    i64 n_ac = m / lcm(a, c);
    i64 n_bc = m / lcm(b, c);
    i64 n_abc = m / lcm(lcm(a, b), c);

    cout << 6 * n_a - 3 * (n_ab + n_ac) + 2 * n_abc << " ";
    cout << 6 * n_b - 3 * (n_ab + n_bc) + 2 * n_abc << " ";
    cout << 6 * n_c - 3 * (n_bc + n_ac) + 2 * n_abc << "\n";
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
