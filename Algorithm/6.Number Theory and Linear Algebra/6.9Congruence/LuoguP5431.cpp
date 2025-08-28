#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int MOD;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
void solve() {
    int n, k;
    cin >> n >> MOD >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[0] = 1;
    vector<int> suf(n + 2, 1);
    for(int i = n; i >= 1; i--) {
        suf[i] = 1LL * suf[i + 1] * a[i] % MOD;
    }
    int ans = 0, pre = 1, t = 1;
    for(int i = 1; i <= n; i++) {
        t = 1LL * t * k % MOD;
        pre = 1LL * pre * a[i - 1] % MOD;
        add(ans, 1LL * t * pre % MOD * suf[i + 1] % MOD);
    }
    ans = 1LL * ans * inv(suf[1]) % MOD;
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
