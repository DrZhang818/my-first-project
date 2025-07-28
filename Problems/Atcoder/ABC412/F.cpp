#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

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
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, c;
    cin >> n >> c;
    vector<vector<int>> adj(3005);
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(i == c) x++;
        sum += x;
        adj[x].push_back(i);
    }
    sum--;
    int inv_sum = inv(sum);
    vector<int> dp(n + 1);
    int cnt = 0, tot = 0;
    for(int i = 3001; i >= 1; i--) {
        int q = 1LL * sum * inv(cnt + i - 1) % MOD;
        int p = 1LL * inv_sum * tot % MOD;
        add(p, 1);
        int ans = 1LL * p * q % MOD;
        for(int x : adj[i]) {
            dp[x] = ans;
            add(tot, int(1LL * i * ans % MOD));
            cnt += i;
        }
    }
    cout << dp[c] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
