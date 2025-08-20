#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://codeforces.com/contest/1970/problem/E3
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
struct Matrix {
    vector<vector<int>> mat;
    int n, m;
    Matrix(int n, int m) : mat(n, vector<int>(m)), n(n), m(m) {}
    friend Matrix operator * (const Matrix &a, const Matrix &b) { 
        int n = a.n, m = b.m;
        Matrix res(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < a.m; k++) {
                    add(res.mat[i][j], 1LL * a.mat[i][k] * b.mat[k][j] % MOD);
                }
            }
        }
        return res;
    };
};
Matrix fast_pow(Matrix a, int b) {
    int n = a.n;
    Matrix res(n, n);
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
    Matrix B(m, 2), C(2, m);
    for(int i = 0; i < m; i++) {
        B.mat[i][0] = (c0[i] + c1[i]) % MOD;
        B.mat[i][1] = c0[i];
    }
    for(int j = 0; j < m; j++) {
        C.mat[0][j] = c0[j];
        C.mat[1][j] = c1[j];
    }
    Matrix CB = C * B;
    CB = fast_pow(CB, n - 1);
    Matrix v0(m, 1);
    v0.mat[0][0] = 1;
    v0 = C * v0;
    v0 = CB * v0;
    v0 = B * v0;
    int ans = 0;
    for(int i = 0; i < m; i++) {
        add(ans, v0.mat[i][0]);
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
