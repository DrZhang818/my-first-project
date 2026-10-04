#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct LinearSieve {
    int n;
    vector<int> primes, minp, phi, mu;
    LinearSieve(int n_ = 0) : n(n_), minp(n_ + 1), phi(n_ + 1), mu(n_ + 1) {
        if(n < 1) {
            return;
        }
        phi[1] = 1;
        mu[1] = 1;
        for(int i = 2; i <= n; i++) {
            if(minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
                phi[i] = i - 1;
                mu[i] = -1;
            }
            for(int p : primes) {
                i64 v = 1LL * i * p;
                if(v > n) {
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
    }
};
