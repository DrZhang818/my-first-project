#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll l, r;
    cin >> l >> r;
    ll a = l + r, b = r - l + 1;
    if(a & 1) {
        b >>= 1;
    } else {
        a >>= 1;
    }
    cout << a % 9 * b % 9 << "\n";
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
