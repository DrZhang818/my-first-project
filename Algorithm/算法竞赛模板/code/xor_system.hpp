#pragma once
#include <bits/stdc++.h>
using namespace std;
// 行向量 a[i]：低 m 位是变量系数，第 m+k 位是第 k 个右端项
template <int MAXC> struct XorLinearSystem {
    using B = bitset<MAXC>;
    int n, m, p;
    vector<B> a;
    vector<int> where; // 主元变量所在行，-1 表示自由变量
    XorLinearSystem(int n_, int m_, int p_) : n(n_), m(m_), p(p_), a(n_), where(m_, -1) {
    }
    void setCoeff(int row, int col, bool v) {
        a[row].set(col, v);
    }
    void setRhs(int row, int k, bool v) {
        a[row].set(m + k, v);
    }
    bool solve() {
        where.assign(m, -1);
        int r = 0;
        for(int c = 0; c < m && r < n; c++) {
            int s = -1;
            for(int i = r; i < n; i++) {
                if(a[i][c]) {
                    s = i;
                    break;
                }
            }
            if(s == -1) {
                continue;
            }
            swap(a[r], a[s]);
            where[c] = r;
            for(int i = 0; i < n; i++) {
                if(i != r && a[i][c]) {
                    a[i] ^= a[r];
                }
            }
            r++;
        }
        for(int i = 0; i < n; i++) {
            bool lhs = false;
            bool rhs = false;
            for(int j = 0; j < m; j++) {
                lhs |= a[i][j];
            }
            for(int k = 0; k < p; k++) {
                rhs |= a[i][m + k];
            }
            if(!lhs && rhs) {
                return false;
            }
        }
        return true;
    }
    // 仅在 solve() 返回 true 后调用；x[var][k] 为第 k 个右端项下该变量的取值
    vector<vector<int>> answer() const {
        vector<vector<int>> x(m, vector<int>(p, 0));
        for(int c = 0; c < m; c++) {
            if(where[c] == -1) {
                continue;
            }
            int row = where[c];
            for(int k = 0; k < p; k++) {
                x[c][k] = a[row][m + k] ? 1 : 0;
            }
        }
        return x;
    }
};
