#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int x1, x2;
    cin >> x1 >> x2;

    if(x1 > x2) {
        cout << 1 << " " << 1 << "\n";
        return;
    }

    i64 ans = 1E18, l = -1, r = -1;
    for(int k = 0; k < x1; k++) {
        i64 M = (x2 - 1 - k) >> 1;

        i64 cur = 0, prod = 1;
        for(int i = 19; i >= 0; i--) {
            prod *= (k >> i & 1) ? 2 : 1;
            if(M >> i & 1) {
                cur += prod * (1 << i);
                if(k >> i & 1) {
                    prod = 0;
                    break;
                }
            } 
        }
        cur += prod;

        if(cur < ans) {
            ans = cur;
            l = 1;
            r = x1 - k;
        }
    }

    cout << l << " " << r << "\n";
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