#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
struct Matrix {
    vector<vector<int>> mat;
    Matrix() : mat(2, vector<int>(2)) {}
    friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix res;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 2; k++) {
                    add(res.mat[i][j], 1LL * a.mat[i][k] * b.mat[k][j] % MOD);
                }
            }
        }
        return res;
    }
};
Matrix fast_pow(Matrix a, ll b) {
    Matrix res;
    for(int i = 0; i < 2; i++) {
        res.mat[i][i] = 1;
    }
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}
Matrix mat;
int fib(ll x) {
    Matrix a = fast_pow(mat, x - 1);
    return a.mat[0][0];
}

void solve() {
    int n;
    ll S;
    cin >> n >> S;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<int> dp(n + 1);
    int ans = fib(S);
    for(int i = 1; i <= n; i++) {
        ll cnt = fib(a[i]);
        for(int j = 1; j < i; j++) {
            cnt = mod(cnt - 1LL * dp[j] * fib(a[i] - a[j]) % MOD);
        }
        ans = mod(ans - cnt * fib(S - a[i]) % MOD);
        dp[i] = cnt;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    mat.mat[0][0] = mat.mat[0][1] = mat.mat[1][0] = 1;
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
