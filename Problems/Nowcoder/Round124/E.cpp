#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    int ans = fast_pow(2, n / 2);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}