#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Combination {
    int mod;
    vector<int> fac, ifac;
    Combination(int n, int p) : mod(p) {
        int limit = min(n, p - 1);
        fac.assign(limit + 1, 1);
        for(int i = 1; i <= limit; i++) {
            fac[i] = int(1LL * fac[i - 1] * i % p);
        }
        ifac.assign(limit + 1, 1);
        ifac[limit] = powerMod(fac[limit], p - 2, p);
        for(int i = limit; i >= 1; i--) {
            ifac[i - 1] = int(1LL * ifac[i] * i % p);
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
    int C(i64 n, i64 k) const {
        if(k < 0 || k > n) {
            return 0;
        }
        assert(n < mod && n < (i64)fac.size());
        int nn = int(n);
        int kk = int(k);
        return int(1LL * fac[nn] * ifac[kk] % mod * ifac[nn - kk] % mod);
    }
};
