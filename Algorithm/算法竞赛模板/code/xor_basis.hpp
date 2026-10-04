#pragma once
#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
struct XorBasis {
    array<u64, 64> b{};
    int num = 0;
    bool zero = false;
    vector<u64> basis;
    bool insert(u64 v) {
        for(int i = 63; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                num++;
                basis.clear();
                return true;
            }
            v ^= b[i];
        }
        zero = true;
        return false;
    }
    bool decompose(u64 v) const {
        for(int i = 63; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                return false;
            }
            v ^= b[i];
        }
        return true;
    }
    u64 maxXor() const {
        u64 res = 0;
        for(int i = 63; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    u64 maxWith(u64 v) const {
        u64 res = v;
        for(int i = 63; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
    bool minXor(u64& ans) const {
        if(zero) {
            ans = 0;
            return true;
        }
        for(int i = 0; i < 64; i++) {
            if(b[i]) {
                ans = b[i];
                return true;
            }
        }
        return false;
    }
    void reduce() {
        if(!basis.empty()) {
            return;
        }
        vector<u64> tmp(b.begin(), b.end());
        for(int i = 0; i < 64; i++) {
            if(tmp[i] == 0) {
                continue;
            }
            for(int j = i - 1; j >= 0; j--) {
                if(tmp[i] >> j & 1) {
                    tmp[i] ^= tmp[j];
                }
            }
            basis.push_back(tmp[i]);
        }
    }
    bool kth(u64 k, u64& res) {
        if(k == 0) {
            return false;
        }
        reduce();
        if(zero) {
            k--;
        }
        if(basis.size() < 64 && k >= (u64(1) << basis.size())) {
            return false;
        }
        res = 0;
        for(int i = 0; i < int(basis.size()); i++) {
            if(k >> i & 1) {
                res ^= basis[i];
            }
        }
        return true;
    }
    void merge(const XorBasis& other) {
        zero = zero || other.zero;
        for(int i = 63; i >= 0; i--) {
            if(other.b[i]) {
                insert(other.b[i]);
            }
        }
    }
};
