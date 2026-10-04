#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
i128 exgcd(i128 a, i128 b, i128& x, i128& y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    i128 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
bool invMod(i64 a, i64 m, i64& ans) {
    if(m <= 0) {
        return false;
    }
    a = (i128(a) % m + m) % m;
    i128 x, y;
    if(exgcd(a, m, x, y) != 1) {
        return false;
    }
    ans = (x % m + m) % m;
    return true;
}
// Return 0: inconsistent, 1: success, -1: resulting modulus exceeds i64.
int crtMerge(i64 a, i64 m, i64 b, i64 n, i64& r, i64& mod) {
    assert(m > 0 && n > 0);
    a = (i128(a) % m + m) % m;
    b = (i128(b) % n + n) % n;
    i128 x, y, g = exgcd(m, n, x, y), d = i128(b) - a;
    if(d % g) {
        return 0;
    }
    i128 q = n / g, k = (d / g * x % q + q) % q, M = i128(m) * q;
    if(M > LLONG_MAX) {
        return -1;
    }
    r = (a + i128(m) * k) % M;
    mod = M;
    return 1;
}
int crt(const vector<pair<i64, i64>>& e, i64& r, i64& mod) {
    r = 0;
    mod = 1;
    for(auto [a, m] : e) {
        int z = crtMerge(r, mod, a, m, r, mod);
        if(z != 1) {
            return z;
        }
    }
    return 1;
}
