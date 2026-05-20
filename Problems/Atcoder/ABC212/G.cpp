#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

i64 getPhi(i64 x) {
    i64 res = 1;
    for(i64 p = 2; p * p <= x; p++) {
        if(x % p) continue;
        res *= (p - 1);
        x /= p;
        while(x % p == 0) {
            res *= p;
            x /= p;
        }
    }
    if(x > 1) {
        res *= (x - 1);
    }
    return res;
}

void solve() {
    i64 P;
    cin >> P;

    i64 phi_P = P - 1;

    vector<i64> divs;
    for(i64 i = 1; i * i <= phi_P; i++) {
        if(phi_P % i == 0) {
            divs.push_back(i);
            if(i * i != phi_P) {
                divs.push_back(phi_P / i);
            }
        }
    }

    int ans = 1;

    for(auto d : divs) {
        add(ans, 1LL * (d % MOD) * (getPhi(d) % MOD) % MOD);
    }

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
