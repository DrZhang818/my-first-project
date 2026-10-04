#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <class T, class Op> struct Doubling {
    int log;
    T identity;
    Op op;
    vector<vector<int>> next;
    vector<vector<T>> value;
    Doubling(const vector<int>& to, const vector<T>& weight, i64 maxStep, T identity_,
             Op op_ = Op())
        : log(1), identity(identity_), op(op_) {
        for(i64 x = maxStep; x > 1; x >>= 1) {
            log++;
        }
        next.assign(log, vector<int>(to.size()));
        value.assign(log, vector<T>(to.size()));
        next[0] = to;
        value[0] = weight;
        for(int j = 0; j < log; j++) {
            value[j][0] = identity;
        }
        for(int j = 1; j < log; j++) {
            for(int x = 1; x < int(to.size()); x++) {
                next[j][x] = next[j - 1][next[j - 1][x]];
                value[j][x] = op(value[j - 1][x], value[j - 1][next[j - 1][x]]);
            }
        }
    }
    pair<int, T> jump(int x, i64 k) const {
        T res = identity;
        for(int j = 0; j < log; j++) {
            if(k >> j & 1) {
                res = op(res, value[j][x]);
                x = next[j][x];
            }
        }
        return {x, res};
    }
};
