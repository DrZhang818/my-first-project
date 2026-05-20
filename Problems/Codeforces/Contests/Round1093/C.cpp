#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    i64 p, q;
    cin >> p >> q;

    i64 S = p + 2 * q;
    i64 K = 2 * S + 1;

    for(i64 i = 3; i * i <= K; i += 2) {
        if(K % i == 0) {
            i64 A = i;
            i64 B = K / i;

            i64 n = A - 1 >> 1;
            i64 m = B - 1 >> 1;

            i64 mx = min((n + 1) * m, (m + 1) * n);
            if(q <= mx) {
                cout << n << " " << m << "\n";
                return;
            }
        }
    }

    cout << -1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}