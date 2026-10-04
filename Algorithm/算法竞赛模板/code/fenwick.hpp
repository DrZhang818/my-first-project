#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <class T = i64> struct BIT {
    int n;
    vector<T> tr;
    BIT(int n_ = 0) : n(n_), tr(n_ + 1) {
    }
    void add(int x, T v) {
        for(; x <= n; x += x & -x) {
            tr[x] += v;
        }
    }
    T query(int x) const {
        T res{};
        for(; x > 0; x -= x & -x) {
            res += tr[x];
        }
        return res;
    }
    T query(int l, int r) const {
        return query(r) - query(l - 1);
    }
    int select(T k) const {
        int x = 0;
        T cur{};
        int step = (n ? 1 << (31 - __builtin_clz((unsigned)n)) : 0);
        for(; step; step >>= 1) {
            if(x + step <= n && cur + tr[x + step] < k) {
                x += step;
                cur += tr[x];
            }
        }
        return x + 1;
    }
};
