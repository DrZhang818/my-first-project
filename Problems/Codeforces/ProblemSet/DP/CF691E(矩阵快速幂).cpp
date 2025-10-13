#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

using Matrix = vector<vector<int>>;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

Matrix operator * (const Matrix &a, const Matrix &b) {
    int n = a.size();
    Matrix res(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            if(a[i][k] == 0) continue;
            for(int j = 0; j < n; j++) {
                add(res[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
    return res;
}

Matrix fast_pow(Matrix &a, ll b) {
    int n = a.size();
    Matrix res(n, vector<int>(n));
    for(int i = 0; i < n; i++) res[i][i] = 1;
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    Matrix dp(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            ll x = a[i] ^ a[j];
            dp[i][j] = dp[j][i] = (__builtin_popcountll(x) % 3 == 0 ? 1 : 0);
        }
    }
    dp = fast_pow(dp, k - 1);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            add(ans, dp[i][j]);
        }
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
