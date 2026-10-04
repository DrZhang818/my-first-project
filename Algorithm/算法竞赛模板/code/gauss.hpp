#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
constexpr db EPS = 1e-9;
int gaussDouble(vector<vector<db>>& a, vector<int>& pivotCol, db eps = EPS,
                int variables = -1) {
    int n = int(a.size()) - 1;
    int m = n > 0 ? int(a[1].size()) - 1 : 0;
    pivotCol.assign(m + 1, 0);
    if(n <= 0) {
        return 0;
    }
    int row = 1;
    int limit = variables < 0 ? m - 1 : variables;
    assert(0 <= limit && limit <= m);
    for(int col = 1; col <= limit && row <= n; col++) {
        int best = row;
        for(int i = row + 1; i <= n; i++) {
            if(fabs(a[i][col]) > fabs(a[best][col])) {
                best = i;
            }
        }
        if(fabs(a[best][col]) < eps) {
            continue;
        }
        swap(a[best], a[row]);
        db inv = 1.0 / a[row][col];
        for(int j = col; j <= m; j++) {
            a[row][j] *= inv;
        }
        for(int i = 1; i <= n; i++) {
            if(i == row) {
                continue;
            }
            db fac = a[i][col];
            for(int j = col; j <= m; j++) {
                a[i][j] -= fac * a[row][j];
            }
        }
        pivotCol[col] = row++;
    }
    return row - 1;
}
int gaussMod(vector<vector<int>>& a, int mod, vector<int>& pivotCol, int variables = -1) {
    int n = int(a.size()) - 1;
    int m = n > 0 ? int(a[1].size()) - 1 : 0;
    pivotCol.assign(m + 1, 0);
    if(n <= 0) {
        return 0;
    }
    int row = 1;
    auto powerMod = [&](int x, i64 e) {
        int res = 1;
        while(e > 0) {
            if(e & 1) {
                res = int(1LL * res * x % mod);
            }
            x = int(1LL * x * x % mod);
            e >>= 1;
        }
        return res;
    };
    int limit = variables < 0 ? m - 1 : variables;
    assert(0 <= limit && limit <= m);
    for(int col = 1; col <= limit && row <= n; col++) {
        int best = 0;
        for(int i = row; i <= n; i++) {
            if(a[i][col] != 0) {
                best = i;
                break;
            }
        }
        if(best == 0) {
            continue;
        }
        swap(a[best], a[row]);
        int inv = powerMod(a[row][col], mod - 2);
        for(int j = col; j <= m; j++) {
            a[row][j] = int(1LL * a[row][j] * inv % mod);
        }
        for(int i = 1; i <= n; i++) {
            if(i == row) {
                continue;
            }
            int fac = a[i][col];
            for(int j = col; j <= m; j++) {
                a[i][j] = int((a[i][j] - 1LL * fac * a[row][j] % mod + mod) % mod);
            }
        }
        pivotCol[col] = row++;
    }
    return row - 1;
}
int gaussXor(vector<vector<int>>& a, vector<int>& pivotCol, int variables = -1) {
    int n = int(a.size()) - 1;
    int m = n > 0 ? int(a[1].size()) - 1 : 0;
    pivotCol.assign(m + 1, 0);
    if(n <= 0) {
        return 0;
    }
    int row = 1;
    int limit = variables < 0 ? m - 1 : variables;
    assert(0 <= limit && limit <= m);
    for(int col = 1; col <= limit && row <= n; col++) {
        int best = 0;
        for(int i = row; i <= n; i++) {
            if(a[i][col]) {
                best = i;
                break;
            }
        }
        if(best == 0) {
            continue;
        }
        swap(a[best], a[row]);
        for(int i = 1; i <= n; i++) {
            if(i != row && a[i][col]) {
                for(int j = col; j <= m; j++) {
                    a[i][j] ^= a[row][j];
                }
            }
        }
        pivotCol[col] = row++;
    }
    return row - 1;
}
