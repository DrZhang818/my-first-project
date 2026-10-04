#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;
struct PollardRho {
    static u64 mulMod(u64 a, u64 b, u64 m) {
        return u64(u128(a) * b % m);
    }
    static u64 powerMod(u64 a, u64 e, u64 m) {
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
    static bool isPrime(u64 n) {
        if(n < 2) {
            return false;
        }
        for(u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL,
                     31ULL, 37ULL}) {
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
        for(u64 a :
            {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
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
    static i64 f(i64 x, i64 c, i64 n) {
        return i64((u128(x) * x + u64(c)) % u64(n));
    }
    static i64 pollard(i64 n, mt19937_64& rng) {
        if(n % 2 == 0) {
            return 2;
        }
        while(true) {
            i64 c = i64(rng() % (n - 1)) + 1;
            i64 x = i64(rng() % (n - 1)) + 1;
            i64 y = x;
            i64 d = 1;
            while(d == 1) {
                x = f(x, c, n);
                y = f(f(y, c, n), c, n);
                i64 diff = x > y ? x - y : y - x;
                d = std::gcd(diff, n);
            }
            if(d != n) {
                return d;
            }
        }
    }
    static void factorRec(i64 n, mt19937_64& rng, vector<i64>& out) {
        if(n <= 1) {
            return;
        }
        if(isPrime(u64(n))) {
            out.push_back(n);
            return;
        }
        if(n % 2 == 0) {
            out.push_back(2);
            factorRec(n / 2, rng, out);
            return;
        }
        i64 d = pollard(n, rng);
        factorRec(d, rng, out);
        factorRec(n / d, rng, out);
    }
    static vector<i64> factorize(i64 n) {
        vector<i64> out;
        if(n <= 1) {
            return out;
        }
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        factorRec(n, rng, out);
        sort(out.begin(), out.end());
        return out;
    }
    static vector<i64> factorize(i64 n, u64 seed) {
        vector<i64> out;
        if(n <= 1) {
            return out;
        }
        mt19937_64 rng(seed);
        factorRec(n, rng, out);
        sort(out.begin(), out.end());
        return out;
    }
};
