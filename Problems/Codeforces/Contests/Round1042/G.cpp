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
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> h(32);
    vector<int> dp(32);
    h[1] = 1, dp[1] = 1;
    for(int i = 2; i <= 31; i++) {
        h[i] = 1LL * h[i - 1] * h[i - 1] % MOD * i % MOD;
        dp[i] = 1LL * h[i] * inv(h[i - 1]) % MOD;
    }
    ll ans = 1;
    sort(a.begin() + 1, a.end());
    auto dfs = [&](this auto &&self, int k, int x) -> void {
        if(k == 0) return;
        for(int i = 1; i <= x && k > 0; i++) {
            if(k >= (1 << i - 1)) {
                k -= (1 << i - 1);
                ans = ans * dp[i] % MOD;
            } else {
                ans = ans * i % MOD;
                self(k - 1, i - 1);
                break;
            }
        }
    };
    for(int i = 1; i <= n && k > 0; i++) {
        if(a[i] >= 31) {
            ans = ans * a[i] % MOD;
            dfs(k - 1, a[i] - 1);
            break;
        } 
        if(k >= (1 << a[i] - 1)) {
            k -= (1 << a[i] - 1);
            ans = ans * dp[a[i]] % MOD;
        } else {
            ans = ans * a[i] % MOD;
            dfs(k - 1, a[i] - 1);
            break;
        }
    }
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
