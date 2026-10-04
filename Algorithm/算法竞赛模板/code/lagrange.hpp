#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int powerMod(int a, i64 e, int p) {
    int res = 1;
    while(e > 0) {
        if(e & 1) {
            res = int(1LL * res * a % p);
        }
        a = int(1LL * a * a % p);
        e >>= 1;
    }
    return res;
}
int lagrange(const vector<int>& y, i64 x, int p) {
    int n = int(y.size()) - 1;
    if(n < 0) {
        return 0;
    }
    if(0 <= x && x <= n) {
        return y[int(x)];
    }
    i64 v = x % p;
    if(v < 0) {
        v += p;
    }
    vector<int> fac(n + 1, 1), ifac(n + 1);
    for(int i = 1; i <= n; i++) {
        fac[i] = int(1LL * fac[i - 1] * i % p);
    }
    ifac[n] = powerMod(fac[n], p - 2, p);
    for(int i = n; i >= 1; i--) {
        ifac[i - 1] = int(1LL * ifac[i] * i % p);
    }
    vector<int> pre(n + 1, 1), suf(n + 2, 1);
    for(int i = 1; i <= n; i++) {
        int d = int(v - (i - 1));
        if(d < 0) {
            d += p;
        }
        pre[i] = int(1LL * pre[i - 1] * d % p);
    }
    for(int i = n - 1; i >= 0; i--) {
        int d = int(v - (i + 1));
        if(d < 0) {
            d += p;
        }
        suf[i] = int(1LL * suf[i + 1] * d % p);
    }
    i64 res = 0;
    for(int i = 0; i <= n; i++) {
        int cur = int(1LL * y[i] * pre[i] % p * suf[i] % p * ifac[i] % p * ifac[n - i] % p);
        if((n - i) & 1) {
            res -= cur;
            if(res < 0) {
                res += p;
            }
        } else {
            res += cur;
            if(res >= p) {
                res -= p;
            }
        }
    }
    return res;
}
