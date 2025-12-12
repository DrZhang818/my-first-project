#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 1000000007;
constexpr int N = 105;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int fac[N + 1];

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        sum += b[i];
    }

    vector<int> cnt(sum + 1);
    for(int i = 1; i <= n; i++) {
        if(a[i] <= sum) {
            cnt[a[i]]++;
        }
    } 

    vector<vector<int>> dp(n + 1, vector<int>(sum + 1));
    dp[0][0] = 1;

    map<PII,int> mp;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        for(int k = 1; k <= i && k <= n - 1; k++) {
            for(int x = b[i]; x <= sum; x++) {
                add(ndp[k][x], dp[k - 1][x - b[i]]);
                add(ans, 1LL * fac[k] * fac[n - 1 - k] % MOD * dp[k - 1][x - b[i]] % MOD * (cnt[x] - (x == a[i])) % MOD);
                add(ans, MOD - mp[{k - 1,x - b[i]}][x]);
                if(a[i] <= sum) {
                    add(mp[{k, x}][a[i]], )
                }
                cerr << "! " << i << " " << k << " " << x << " " << ans << "\n";
            }
        }
        swap(dp, ndp);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);    
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= N - 1; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}