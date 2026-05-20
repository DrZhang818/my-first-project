#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void print(i128 x) {
    if(x == 0) {
        cout << 0 << "\n";
        return;
    }
    bool neg = x < 0 ? 1 : 0;
    if(neg) x = -x;
    string s;
    while(x) {
        s += char('0' + x % 10);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    if(neg) cout << '-';
    cout << s << "\n";
}

void solve() {
    i64 a, b, k;
    cin >> a >> b >> k;

    if(a == 1 || b == 1 || min(a, b) + k >= max(a, b)) {
        cout << max(a, b) << "\n";
        return;
    }

    i128 ans = (i128)1 << 120;
    i64 u = a - 1, v = b - 1;
    for(i64 L = 1, R; L <= a || L <= b; L = R + 1) {
        if(L <= u && L <= v) {
            R = min(u / (u / L), v / (v / L));
        } else if(L <= u) {
            R = u / (u / L);
        } else if(L <= v) {
            R = v / (v / L);
        } else {
            R = max(a, b);
        }
        i64 g = L;
        i64 x = u / g + 1;
        i64 y = v / g + 1;
        if(i128(x) * g > a + k || i128(y) * g > b + k) continue;
        ans = min(ans, i128(g) * x * y);
    }

    print(ans);
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