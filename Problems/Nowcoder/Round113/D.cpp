#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    int fac = 1;
    for(int i = 1; i < n; i++) {
        fac = 1LL * fac * i % MOD;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int x = i % 5;
        add(ans, 1LL * fac * x % MOD);
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
