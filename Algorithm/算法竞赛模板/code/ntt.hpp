#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int MOD = 998244353;
constexpr int G = 3;
constexpr int MAX_NTT_SIZE = 1 << 23;
int normalize(i64 x) {
    x %= MOD;
    if(x < 0) {
        x += MOD;
    }
    return int(x);
}
int powerMod(int a, int b) {
    a = normalize(a);
    int res = 1;
    while(b > 0) {
        if(b & 1) {
            res = int(1LL * res * a % MOD);
        }
        a = int(1LL * a * a % MOD);
        b >>= 1;
    }
    return res;
}
void ntt(vector<int>& a, bool invert) {
    int n = int(a.size());
    if(n <= 1) {
        return;
    }
    assert((n & (n - 1)) == 0);
    assert(n <= MAX_NTT_SIZE);
    assert((MOD - 1) % n == 0);
    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while(j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if(i < j) {
            swap(a[i], a[j]);
        }
    }
    for(int len = 2; len <= n; len <<= 1) {
        int wlen = powerMod(G, (MOD - 1) / len);
        if(invert) {
            wlen = powerMod(wlen, MOD - 2);
        }
        int half = len >> 1;
        for(int left = 0; left < n; left += len) {
            i64 w = 1;
            for(int j = 0; j < half; j++) {
                int u = a[left + j];
                int v = int(w * a[left + j + half] % MOD);
                int sum = u + v;
                if(sum >= MOD) {
                    sum -= MOD;
                }
                int diff = u - v;
                if(diff < 0) {
                    diff += MOD;
                }
                a[left + j] = sum;
                a[left + j + half] = diff;
                w = w * wlen % MOD;
            }
        }
    }
    if(invert) {
        int invN = powerMod(n, MOD - 2);
        for(int& x : a) {
            x = int(1LL * x * invN % MOD);
        }
    }
}
vector<int> convolutionNaive(const vector<int>& a, const vector<int>& b) {
    if(a.empty() || b.empty()) {
        return {};
    }
    vector<int> c(a.size() + b.size() - 1);
    for(int i = 0; i < int(a.size()); i++) {
        for(int j = 0; j < int(b.size()); j++) {
            c[i + j] = int((c[i + j] + 1LL * a[i] * b[j]) % MOD);
        }
    }
    return c;
}
vector<int> convolution(vector<int> a, vector<int> b) {
    if(a.empty() || b.empty()) {
        return {};
    }
    for(int& x : a) {
        x = normalize(x);
    }
    for(int& x : b) {
        x = normalize(x);
    }
    int resSize = int(a.size() + b.size() - 1);
    if(1LL * a.size() * b.size() <= 4096) {
        return convolutionNaive(a, b);
    }
    assert(resSize <= MAX_NTT_SIZE);
    int n = 1;
    while(n < resSize) {
        n <<= 1;
    }
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for(int i = 0; i < n; i++) {
        a[i] = int(1LL * a[i] * b[i] % MOD);
    }
    ntt(a, true);
    a.resize(resSize);
    return a;
}
vector<int> convolutionTrunc(vector<int> a, vector<int> b, int limit) {
    if(limit <= 0) {
        return {};
    }
    if(int(a.size()) > limit) {
        a.resize(limit);
    }
    if(int(b.size()) > limit) {
        b.resize(limit);
    }
    vector<int> c = convolution(a, b);
    if(int(c.size()) > limit) {
        c.resize(limit);
    }
    return c;
}
