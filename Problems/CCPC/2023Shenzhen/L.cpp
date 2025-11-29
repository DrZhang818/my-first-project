#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = int(1E9) + 9;

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int M, K;
    cin >> M >> K;
    int ans = 1LL * M * K % MOD;
    int M2 = 1LL * M * M % MOD;
    for(int i = 1, L = 1; i <= K - 1; i++) {
        add(L, M - 1);
        add(ans, 1LL * M2 * (K - i) % MOD * fast_pow(L, MOD - 2) % MOD);
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
