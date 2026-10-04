#pragma once
#include <bits/stdc++.h>
using namespace std;
template <class T, class F> struct ST {
    int n;
    vector<vector<T>> st;
    F op;
    ST(const vector<T>& a, F f) : n(int(a.size()) - 1), op(move(f)) {
        int m = int((n ? 32 - __builtin_clz((unsigned)n) : 0));
        st.assign(m, vector<T>(n + 1));
        if(n == 0) {
            return;
        }
        st[0] = a;
        for(int k = 1; k < m; k++) {
            for(int i = 1; i + (1 << k) - 1 <= n; i++) {
                st[k][i] = this->op(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    T query(int l, int r) const {
        int k = int((32 - __builtin_clz((unsigned)(r - l + 1)))) - 1;
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
