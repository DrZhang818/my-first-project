#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://codeforces.com/contest/1970/problem/E2
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
struct Matrix {
    vector<vector<int>> mat;
    int n;
    Matrix(int n) : mat(n, vector<int>(n)), n(n) {}
    Matrix operator * (const Matrix &b) const {
        Matrix res(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < n; k++) {
                    add(res.mat[i][j], 1LL * mat[i][k] * b.mat[k][j] % MOD);
                }
            }
        }
        return res;
    };
};
Matrix fast_pow(Matrix a, int b) {
    int n = a.mat.size();
    Matrix res(n);
    for(int i = 0; i < n; i++) {
        res.mat[i][i] = 1;
    }
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
void solve() {
    int m, n;
    cin >> m >> n;
    vector<int> c0(m), c1(m);
    for(int i = 0; i < m; i++) {
        cin >> c0[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> c1[i];
    }
    vector x(m, vector<int>(m));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            x[i][j] = (1LL * c0[j] * (c0[i] + c1[i]) % MOD + 1LL * c1[j] * c0[i] % MOD) % MOD;
        }
    }
    Matrix a(m);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            a.mat[i][j] = x[j][i];
        }
    }
    a = fast_pow(a, n);
    int ans = 0;
    for(int i = 0; i < m; i++) {
        add(ans, a.mat[i][0]);
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
