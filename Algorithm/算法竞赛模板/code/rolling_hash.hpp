#pragma once
#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
struct RollingHash {
    u64 base;
    vector<u64> pw, h;
    RollingHash(const string& s, u64 base_ = 19260817) : base(base_) {
        string t = " " + s;
        int n = int(s.size());
        pw.assign(n + 1, 1);
        h.assign(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            pw[i] = pw[i - 1] * base;
            h[i] = h[i - 1] * base + u64((unsigned char)t[i]) + 1;
        }
    }
    u64 get(int l, int r) const {
        return h[r] - h[l - 1] * pw[r - l + 1];
    }
};
