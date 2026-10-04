#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

int calc(i64 x) {
    int res = 0;
    while(x) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

void solve() {
    i64 x;
    cin >> x;
    while(1) {
        if(gcd(x, calc(x)) > 1) {
            cout << x << "\n";
            return;
        }
        x++;
    }
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