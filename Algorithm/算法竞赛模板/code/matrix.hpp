#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int MOD = 998244353;
struct Matrix {
    int row, col;
    vector<int> mat;
    Matrix(int row_ = 0, int col_ = 0)
        : row(row_), col(col_), mat((row_ + 1) * (col_ + 1)) {
    }
    int& operator()(int i, int j) {
        return mat[i * (col + 1) + j];
    }
    const int& operator()(int i, int j) const {
        return mat[i * (col + 1) + j];
    }
    static Matrix identity(int n) {
        Matrix res(n, n);
        for(int i = 1; i <= n; i++) {
            res(i, i) = 1;
        }
        return res;
    }
};
Matrix operator*(const Matrix& a, const Matrix& b) {
    assert(a.col == b.row);
    Matrix res(a.row, b.col);
    for(int i = 1; i <= a.row; i++) {
        for(int k = 1; k <= a.col; k++) {
            int x = a(i, k);
            if(x == 0) {
                continue;
            }
            for(int j = 1; j <= b.col; j++) {
                res(i, j) = int((res(i, j) + 1LL * x * b(k, j)) % MOD);
            }
        }
    }
    return res;
}
Matrix power(Matrix a, i64 b) {
    assert(a.row == a.col);
    Matrix res = Matrix::identity(a.row);
    while(b > 0) {
        if(b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}
vector<int> operator*(const Matrix& a, const vector<int>& v) {
    assert(a.col + 1 == int(v.size()));
    vector<int> res(a.row + 1, 0);
    for(int i = 1; i <= a.row; i++) {
        for(int j = 1; j <= a.col; j++) {
            res[i] = int((res[i] + 1LL * a(i, j) * v[j]) % MOD);
        }
    }
    return res;
}
