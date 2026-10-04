#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Lucas {
    int p;
    vector<int> fac, ifac;
    Lucas(int p_) : p(p_), fac(p_), ifac(p_) {
        fac[0] = ifac[0] = 1;
        for(int i = 1; i < p; i++) {
            fac[i] = int(1LL * fac[i - 1] * i % p);
        }
        ifac[p - 1] = powerMod(fac[p - 1], p - 2, p);
        for(int i = p - 2; i >= 1; i--) {
            ifac[i] = int(1LL * ifac[i + 1] * (i + 1) % p);
        }
    }
    static int powerMod(int a, i64 e, int p) {
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
    int smallC(int n, int k) const {
        if(k < 0 || k > n) {
            return 0;
        }
        return int(1LL * fac[n] * ifac[k] % p * ifac[n - k] % p);
    }
    int C(i64 n, i64 k) const {
        if(k < 0 || k > n) {
            return 0;
        }
        if(n < p) {
            return smallC(int(n), int(k));
        }
        return int(1LL * smallC(int(n % p), int(k % p)) * C(n / p, k / p) % p);
    }
};
