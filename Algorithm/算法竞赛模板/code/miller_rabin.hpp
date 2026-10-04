#pragma once
#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
using u128 = __uint128_t;
u64 mulMod(u64 a, u64 b, u64 m) {
    return u64(u128(a) * b % m);
}
u64 powerMod(u64 a, u64 e, u64 m) {
    u64 res = 1 % m;
    while(e > 0) {
        if(e & 1) {
            res = mulMod(res, a, m);
        }
        a = mulMod(a, a, m);
        e >>= 1;
    }
    return res;
}
bool isPrime(u64 n) {
    if(n < 2) {
        return false;
    }
    for(u64 p :
        {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if(n % p == 0) {
            return n == p;
        }
    }
    u64 d = n - 1;
    int s = 0;
    while((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for(u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if(a % n == 0) {
            continue;
        }
        u64 x = powerMod(a % n, d, n);
        if(x == 1 || x == n - 1) {
            continue;
        }
        bool composite = true;
        for(int r = 1; r < s; r++) {
            x = mulMod(x, x, n);
            if(x == n - 1) {
                composite = false;
                break;
            }
        }
        if(composite) {
            return false;
        }
    }
    return true;
}
