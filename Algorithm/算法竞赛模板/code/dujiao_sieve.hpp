#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128_t;
struct DuJiaoSieve {
    int limit;
    vector<i64> prefPhi, prefMu;
    unordered_map<i64, pair<i128, i64>> memo;
    DuJiaoSieve(int limit_ = 2000000) : limit(limit_) {
        vector<int> minp(limit + 1), phi(limit + 1), mu(limit + 1);
        prefPhi.assign(limit + 1, 0);
        prefMu.assign(limit + 1, 0);
        if(limit < 1) {
            return;
        }
        phi[1] = 1;
        mu[1] = 1;
        vector<int> primes;
        for(int i = 2; i <= limit; i++) {
            if(!minp[i]) {
                minp[i] = i;
                primes.push_back(i);
                phi[i] = i - 1;
                mu[i] = -1;
            }
            for(int p : primes) {
                i64 v = 1LL * i * p;
                if(v > limit) {
                    break;
                }
                int vv = int(v);
                minp[vv] = p;
                if(i % p == 0) {
                    phi[vv] = phi[i] * p;
                    mu[vv] = 0;
                    break;
                }
                phi[vv] = phi[i] * (p - 1);
                mu[vv] = -mu[i];
            }
        }
        for(int i = 1; i <= limit; i++) {
            prefPhi[i] = prefPhi[i - 1] + phi[i];
            prefMu[i] = prefMu[i - 1] + mu[i];
        }
    }
    pair<i128, i64> get(i64 n) {
        if(n <= 0) {
            return {0, 0};
        }
        if(n <= limit) {
            return {prefPhi[n], prefMu[n]};
        }
        auto it = memo.find(n);
        if(it != memo.end()) {
            return it->second;
        }
        i128 sumPhi = i128(n) * (i128(n) + 1) / 2;
        i64 sumMu = 1;
        for(i64 l = 2, r; l <= n; l = r + 1) {
            r = n / (n / l);
            auto [x, y] = get(n / l);
            sumPhi -= i128(x) * (r - l + 1);
            sumMu -= y * (r - l + 1);
        }
        return memo[n] = {sumPhi, sumMu};
    }
};
