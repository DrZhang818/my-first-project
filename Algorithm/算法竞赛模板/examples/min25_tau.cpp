#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Min25Sieve {
    i64 n;
    int mod;
    int sq;
    vector<int> primes;
    vector<i64> w;
    vector<int> id1, id2;
    vector<i64> g0, g1, g2;
    vector<i64> sp0, sp1, sp2;
    Min25Sieve(i64 n_, int mod_) : n(n_), mod(mod_) {
        assert(n >= 1 && mod > 3);
        sq = int(sqrt((long double)n));
        while(1LL * (sq + 1) * (sq + 1) <= n) {
            ++sq;
        }
        while(1LL * sq * sq > n) {
            --sq;
        }
        id1.assign(sq + 2, -1);
        id2.assign(sq + 2, -1);
        initSieve(sq);
        build();
    }
    // ---- 按题目修改：f(p^e) ----
    i64 fpe(i64 p, int e) const {
        return (e + 1) % mod;
    }
    // f(p) = a0 + a1*p + a2*p^2，默认 a0=0, a1=-1, a2=1（即 p^2-p）
    i64 sumFp(i64 x) const {
        return 2 * g0[get(x)] % mod;
    }
    i64 sumFpPrefix(int j) const {
        return 2 * sp0[j] % mod;
    }
    i64 solve() {
        return (S(n, 0) + 1) % mod;
    }

  private:
    i64 powerMod(i64 a, i64 e, int m) const {
        i64 res = 1 % m;
        a %= m;
        while(e > 0) {
            if(e & 1) {
                res = res * a % m;
            }
            a = a * a % m;
            e >>= 1;
        }
        return res;
    }
    void initSieve(int lim) {
        vector<int> minp(lim + 1);
        sp0.assign(lim + 2, 0);
        sp1.assign(lim + 2, 0);
        sp2.assign(lim + 2, 0);
        for(int i = 2; i <= lim; i++) {
            if(!minp[i]) {
                minp[i] = i;
                primes.push_back(i);
                int j = int(primes.size());
                sp0[j] = sp0[j - 1] + 1;
                sp1[j] = (sp1[j - 1] + i) % mod;
                sp2[j] = (sp2[j - 1] + 1LL * i * i) % mod;
            }
            for(int p : primes) {
                i64 v = 1LL * i * p;
                if(v > lim) {
                    break;
                }
                minp[int(v)] = p;
                if(minp[i] == p) {
                    break;
                }
            }
        }
    }
    void build() {
        for(i64 l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            i64 v = n / l;
            w.push_back(v);
            if(v <= sq) {
                id1[int(v)] = int(w.size()) - 1;
            } else {
                id2[int(n / v)] = int(w.size()) - 1;
            }
        }
        i64 inv2 = powerMod(2, mod - 2, mod);
        i64 inv6 = powerMod(6, mod - 2, mod);
        g0.assign(w.size(), 0);
        g1.assign(w.size(), 0);
        g2.assign(w.size(), 0);
        for(int i = 0; i < int(w.size()); i++) {
            i64 x = w[i] % mod;
            g0[i] = (x - 1 + mod) % mod;
            g1[i] = (x * ((x + 1) % mod) % mod * inv2 % mod - 1 + mod) % mod;
            i64 t = x * ((x + 1) % mod) % mod * ((2 * x + 1) % mod) % mod;
            g2[i] = (t * inv6 % mod - 1 + mod) % mod;
        }
        for(int j = 0; j < int(primes.size()); j++) {
            i64 p = primes[j];
            i64 p2 = p * p;
            for(int i = 0; i < int(w.size()); i++) {
                if(w[i] < p2) {
                    break;
                }
                int k = get(w[i] / p);
                g0[i] = (g0[i] - (g0[k] - sp0[j] + mod) % mod + mod) % mod;
                g1[i] = (g1[i] - p * ((g1[k] - sp1[j] + mod) % mod) % mod + mod) % mod;
                g2[i] =
                    (g2[i] - p2 % mod * ((g2[k] - sp2[j] + mod) % mod) % mod + mod) % mod;
            }
        }
    }
    int get(i64 x) const {
        return x <= sq ? id1[int(x)] : id2[int(n / x)];
    }
    i64 S(i64 x, int j) {
        if(x <= 1 || (j < int(primes.size()) && primes[j] > x)) {
            return 0;
        }
        i64 ans = (sumFp(x) - sumFpPrefix(j) + mod) % mod;
        for(int i = j; i < int(primes.size()); i++) {
            i64 p = primes[i];
            if(p * p > x) {
                break;
            }
            i64 pe = p;
            int e = 1;
            while(pe <= x / p) {
                ans = (ans + fpe(p, e) * S(x / pe, i + 1)) % mod;
                ans = (ans + fpe(p, e + 1)) % mod;
                pe *= p;
                e++;
            }
        }
        return ans;
    }
};

int main() {
    for(int P : {7, 101, 1000000007}) {
        long long sum = 0;
        for(int n = 1; n <= 800; n++) {
            int x = n;
            long long v = 1;
            for(int p = 2; p <= x; p++) {
                if(x % p == 0) {
                    int e = 0;
                    while(x % p == 0) {
                        x /= p, e++;
                    }
                    v *= e + 1;
                }
            }
            sum = (sum + v % P + P) % P;
            assert(Min25Sieve(n, P).solve() == sum);
        }
    }
}
