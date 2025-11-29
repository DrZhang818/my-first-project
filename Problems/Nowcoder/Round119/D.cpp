#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

int fast_pow(ll a, ll b) {
    a %= MOD;
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
    ll k;
    cin >> n >> k;
    ll cur = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(i & 1) {
            cur += x;
        } else {
            cur -= x;
            while(k && cur < 0) {
                k >>= 1;
                cur++;
            }
        }
    }
    if(k == 0) {
        cout << 0 << "\n";
        return;
    }
    int ans = 1LL * (k % MOD) * fast_pow(2, cur) % MOD;
    cout << ans << "\n";
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
