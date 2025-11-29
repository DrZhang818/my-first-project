#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

int inv(int a) {
    return fast_pow(a, MOD - 2);
}

void solve() {
    int n;
    cin >> n;
    if(n == 2) {
        cout << inv(2);
    } else if(n % 2 == 1) {
        cout << 1LL * (n + 1) * inv(2 * n) % MOD;
    } else {
        cout << 1LL * (2 * n + 3) % MOD * inv(4LL * n % MOD) % MOD;
    }
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
