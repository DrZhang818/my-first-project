#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

inline i64 lowbit(i64 x) { return x & -x; }

void solve() {  
    i64 s, m;
    cin >> s >> m;

    i64 low_s = lowbit(s);
    i64 low_m = lowbit(m);

    if(low_s < low_m) {
        cout << -1 << "\n";
        return;
    }
    i64 high_bit = 1LL << (__lg(s) + 1);
    m &= (high_bit - 1);

    auto ck = [&](i64 x) -> bool {
        i64 cur = 0;
        for(int i = 61; i >= 0; i--) {
            cur <<= 1;
            if(s >> i & 1) {
                cur += 1;
            }
            if(m >> i & 1) {
                cur -= min(cur, x);
            }
            if(cur > x) {
                return false;
            }
        }
        return cur == 0;
    };

    i64 lo = -1, hi = (1E18) + 1;

    ck(5);

    while(lo + 1 < hi) {
        i64 mid = lo + hi >> 1;
        if(ck(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    cout << hi << "\n";
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
